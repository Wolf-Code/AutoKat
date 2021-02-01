using AutoKat.Data.Sessions;
using AutoKat.Data.Users.Entities;
using AutoKat.Domain.Users;
using AutoKat.Infrastructure.HttpContext;
using Microsoft.IdentityModel.Tokens;
using System;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;
using System.Threading.Tasks;

namespace AutoKat.Infrastructure.Authentication
{
	public class AuthenticationService : IAuthenticationService
	{
		private readonly string jwtSecret;
		private readonly int jwtLifespan;
		private readonly IHttpContextService httpContextService;
		private readonly ISessionRepository sessionRepository;

		public AuthenticationService(
			string jwtSecret,
			int jwtLifespan,
			IHttpContextService httpContextService,
			ISessionRepository sessionRepository
		)
		{
			this.jwtSecret = jwtSecret;
			this.jwtLifespan = jwtLifespan;
			this.httpContextService = httpContextService;
			this.sessionRepository = sessionRepository;
		}

		public int JwtLifespan => jwtLifespan;

		public UserAuthenticationData GetAuthenticationData(string email)
		{
			var expirationTime = DateTime.UtcNow.AddSeconds(jwtLifespan);

			var tokenDescriptor = new SecurityTokenDescriptor
			{
				Subject = new ClaimsIdentity(new[]
				{
					new Claim(ClaimTypes.Email, email)
				}),
				Expires = expirationTime,
				SigningCredentials = new SigningCredentials(
					new SymmetricSecurityKey(Encoding.UTF8.GetBytes(jwtSecret)),
					SecurityAlgorithms.HmacSha256Signature
				)
			};
			var tokenHandler = new JwtSecurityTokenHandler();
			var token = tokenHandler.WriteToken(tokenHandler.CreateToken(tokenDescriptor));

			return new UserAuthenticationData
			{
				Token = token,
				TokenExpirationTime = ((DateTimeOffset)expirationTime).ToUnixTimeSeconds(),
				Id = email
			};
		}

		public async Task<bool> ValidateTokenWithSession(string token, User user)
		{
			var ip = this.httpContextService.GetCurrentUserIpAddress();
			var session = await this.sessionRepository.GetActiveSession(user, token, ip);

			return session != null;
		}
	}
}
