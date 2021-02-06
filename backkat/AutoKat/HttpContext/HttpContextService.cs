using AutoKat.Domain.Authentication;
using AutoKat.Infrastructure.HttpContext;
using Microsoft.AspNetCore.Http;
using System.Linq;
using System.Net;
using System.Security.Claims;

namespace AutoKat.HttpContext
{
	public class HttpContextService : IHttpContextService
	{
		private readonly IHttpContextAccessor httpContextAccessor;

		public HttpContextService(IHttpContextAccessor httpContextAccessor)
		{
			this.httpContextAccessor = httpContextAccessor;
		}

		public string GetCurrentUserEmail()
		{
			var claim = this.httpContextAccessor.HttpContext.User.FindFirst(ClaimTypes.Email);

			return claim?.Value;
		}

		public IPAddress GetCurrentUserIpAddress()
		{
			return this.httpContextAccessor.HttpContext.Connection.RemoteIpAddress;
		}

		public string GetCookieRefreshToken()
		{
			var cookie = this.httpContextAccessor.HttpContext.Request.Cookies[AuthenticationConstants.RefreshTokenCookie];

			return cookie;
		}

		public string GetHeaderToken()
		{
			var header = this.httpContextAccessor.HttpContext.Request.Headers["Authorization"].FirstOrDefault();
			if (!string.IsNullOrEmpty(header))
			{
				var bearerLength = "Bearer ".Length;
				header = header.Substring(bearerLength, header.Length - bearerLength);
			}

			return header;
		}

		public string GetHeaderRefreshToken()
		{
			var header = this.httpContextAccessor.HttpContext.Request.Headers["RefreshToken"].FirstOrDefault();

			return header;
		}
	}
}
