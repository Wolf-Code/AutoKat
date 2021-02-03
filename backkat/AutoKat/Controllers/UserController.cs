using AutoKat.Domain.Authentication;
using AutoKat.Domain.Users;
using AutoKat.Infrastructure.Users;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Threading.Tasks;

namespace AutoKat.Controllers
{
	[Route("api/[controller]")]
	public class UserController : Controller
	{
		private readonly IUserService userService;

		public UserController(
			IUserService userService
		)
		{
			this.userService = userService;
		}

		[Authorize]
		[HttpGet]
		public async Task<UserInformationResult> GetUserInformation()
		{
			return await this.userService.GetCurrentUserInformation();
		}

		[HttpPost]
		[Route("login")]
		public async Task<UserLoginResult> Login([FromBody] UserLogin login)
		{
			var result = await this.userService.LoginUser(login);

			if (result.Success && login.RememberMe)
			{
				Response.Cookies.Append(AuthenticationConstants.RefreshTokenCookie, result.AuthenticationData.RefreshToken, new Microsoft.AspNetCore.Http.CookieOptions
				{
					SameSite = Microsoft.AspNetCore.Http.SameSiteMode.Lax,
					Expires = DateTimeOffset.FromUnixTimeSeconds(result.AuthenticationData.TokenExpirationTime),
					Secure = true,
					HttpOnly = true,
					Path = "/api/refresh"
				});
			}

			return result;
		}

		[HttpGet]
		[Route("logout")]
		[Authorize]
		public async Task Logout()
		{
			await this.userService.LogoutUser();
			Response.Cookies.Delete(AuthenticationConstants.RefreshTokenCookie);
		}

		[HttpPost]
		public async Task<UserRegistrationResult> Register([FromBody] UserRegistration newUser)
		{
			return await this.userService.RegisterUser(newUser);
		}

		[Authorize]
		[HttpGet]
		[Route("preferences")]
		public async Task<UserPreferences> GetPreferences()
		{
			return await this.userService.GetCurrentUserPreferences();
		}
	}
}
