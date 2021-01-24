using AutoKat.Infrastructure.HttpContext;
using Microsoft.AspNetCore.Http;
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
	}
}
