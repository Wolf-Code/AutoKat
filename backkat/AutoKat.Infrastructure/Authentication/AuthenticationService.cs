using AutoKat.Core.Utilities.DateTime;
using AutoKat.Data.Devices.Entities;
using AutoKat.Data.Sessions;
using AutoKat.Data.Users.Entities;
using AutoKat.Domain.Authentication;
using AutoKat.Infrastructure.Authentication.Exceptions;
using AutoKat.Infrastructure.HttpContext;
using Microsoft.IdentityModel.Tokens;
using System;
using System.Collections.Generic;
using System.IdentityModel.Tokens.Jwt;
using System.Linq;
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
		private readonly IDateTimeProvider dateTimeProvider;

		public AuthenticationService(
			string jwtSecret,
			int jwtLifespan,
			IHttpContextService httpContextService,
			ISessionRepository sessionRepository,
			IDateTimeProvider dateTimeProvider
		)
		{
			this.jwtSecret = jwtSecret;
			this.jwtLifespan = jwtLifespan;
			this.httpContextService = httpContextService;
			this.sessionRepository = sessionRepository;
			this.dateTimeProvider = dateTimeProvider;
		}

		public int JwtLifespan => jwtLifespan;

		public AuthenticationData GetAuthenticationData(User user, string refreshToken = null)
		{
			var email = user.Email;
			var claims = new[]
			{
				new Claim(ClaimTypes.Email, email)
			};

			return this.CreateAuthenticationData(email, claims, refreshToken);
		}

		public AuthenticationData GetAuthenticationData(Device device, string refreshToken)
		{
			var mac = device.MacAddress;
			var claims = new[]
			{
				new Claim(ClaimTypes.SerialNumber, mac)
			};

			return this.CreateAuthenticationData(mac, claims, refreshToken);
		}

		private AuthenticationData CreateAuthenticationData(string id, IEnumerable<Claim> claims, string refreshToken)
		{
			var isRefreshToken = refreshToken == null;

			var now = this.dateTimeProvider.NowUtc;
			var expirationTime = isRefreshToken ? now.AddMonths(1) : now.AddSeconds(jwtLifespan);

			var tokenDescriptor = new SecurityTokenDescriptor
			{
				Subject = new ClaimsIdentity(claims),
				Expires = expirationTime,
				SigningCredentials = new SigningCredentials(
					new SymmetricSecurityKey(Encoding.UTF8.GetBytes(jwtSecret)),
					SecurityAlgorithms.HmacSha256Signature
				)
			};
			var tokenHandler = new JwtSecurityTokenHandler();
			var token = tokenHandler.WriteToken(tokenHandler.CreateToken(tokenDescriptor));

			return new AuthenticationData
			{
				Token = token,
				TokenExpirationTime = ((DateTimeOffset)expirationTime).ToUnixTimeSeconds(),
				Id = id
			};
		}

		public async Task<AuthenticationData> GetNewDeviceToken(string refreshToken)
		{
			var handler = new JwtSecurityTokenHandler();
			var token = handler.ReadJwtToken(refreshToken);

			var mac = token.Claims.First(x => x.Type == "serial").Value;
			var device = await this.sessionRepository.GetDeviceFromRefreshToken(refreshToken);

			if (device.MacAddress == null || device.MacAddress != mac)
			{
				throw new InvalidRefreshTokenException();
			}

			return this.GetAuthenticationData(device, refreshToken);
		}

		public async Task<AuthenticationData> GetNewUserToken(string refreshToken)
		{
			var handler = new JwtSecurityTokenHandler();
			var token = handler.ReadJwtToken(refreshToken);

			var email = token.Claims.First(x => x.Type == "email").Value;
			var user = await this.sessionRepository.GetUserFromRefreshToken(refreshToken);

			if (user == null || user.Email != email)
			{
				throw new InvalidRefreshTokenException();
			}

			return this.GetAuthenticationData(user, refreshToken);
		}

		public async Task<bool> ValidateTokenWithSession(string token, User user)
		{
			var ip = this.httpContextService.GetCurrentUserIpAddress();
			var session = await this.sessionRepository.GetActiveSession(user, token, ip);

			return session != null;
		}

		public async Task<AuthenticationData> GetNewToken(string refreshToken)
		{
			var ip = this.httpContextService.GetCurrentUserIpAddress();
			var session = await this.sessionRepository.GetActiveSession(refreshToken, ip);

			if (session == null)
			{
				throw new InvalidRefreshTokenException();
			}

			if (session.User != null)
			{
				return await this.GetNewUserToken(refreshToken);
			}

			if (session.Device != null)
			{
				return await this.GetNewDeviceToken(refreshToken);
			}

			throw new InvalidRefreshTokenException();
		}
	}
}
