using AutoKat.Domain.Authentication;
using AutoKat.Infrastructure.Authentication;
using AutoKat.Infrastructure.HttpContext;
using Microsoft.AspNetCore.Mvc;
using System.Threading.Tasks;

namespace AutoKat.Controllers
{
	public class AuthenticationController : Controller
	{
		private readonly IHttpContextService httpContextService;
		private readonly IAuthenticationService authenticationService;

		public AuthenticationController(
			IHttpContextService httpContextService,
			IAuthenticationService authenticationService
		)
		{
			this.httpContextService = httpContextService;
			this.authenticationService = authenticationService;
		}

		[HttpGet]
		[Route("~/api/refresh")]
		public async Task<IActionResult> RefreshToken()
		{
			try
			{
				var token = this.httpContextService.GetCookieRefreshToken() ?? this.httpContextService.GetHeaderRefreshToken(); ;
				if (string.IsNullOrEmpty(token))
				{
					return this.Unauthorized();
				}

				var authenticationData = await this.authenticationService.GetNewToken(token);

				return this.Ok(new RefreshTokenResult
				{
					Success = true,
					AuthenticationData = authenticationData
				});
			}
			catch
			{
				return this.Unauthorized();
			}
		}
	}
}
