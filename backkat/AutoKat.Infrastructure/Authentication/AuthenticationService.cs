using AutoKat.Domain.Users;
using Microsoft.IdentityModel.Tokens;
using System;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;

namespace AutoKat.Infrastructure.Authentication
{
	public class AuthenticationService : IAuthenticationService
	{
		private readonly string jwtSecret;
		private readonly int jwtLifespan;

		public AuthenticationService(string jwtSecret, int jwtLifespan)
		{
			this.jwtSecret = jwtSecret;
			this.jwtLifespan = jwtLifespan;

		}

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
	}
}
