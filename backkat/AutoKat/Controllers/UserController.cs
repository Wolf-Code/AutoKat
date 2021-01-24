using AutoKat.Domain.Users;
using AutoKat.Infrastructure.Users;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
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

		[HttpPost]
		[Route("login")]
		public async Task<UserLoginResult> Post([FromBody] UserLogin login)
		{
			return await this.userService.LoginUser(login);
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
