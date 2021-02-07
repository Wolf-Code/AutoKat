using AutoKat.Core.DependencyInjection;
using AutoKat.Core.Users;
using AutoKat.Core.Users.Information;
using AutoKat.Core.Users.Login;
using AutoKat.Core.Users.Registration;
using System.Threading.Tasks;

namespace AutoKat.Services.Users
{
	public interface IUserService : IService
	{
		/// <summary>
		/// Gets the current user's preferences.
		/// </summary>
		/// <returns></returns>
		Task<UserPreferences> GetCurrentUserPreferences();

		/// <summary>
		/// Registers a new user.
		/// </summary>
		/// <param name="newUser">The registration credentials.</param>
		/// <returns>The registrations result.</returns>
		Task<UserRegistrationResponse> RegisterUser(UserRegistrationRequest newUser);

		/// <summary>
		/// Returns the current user's information.
		/// </summary>
		/// <returns>The current user's information</returns>
		Task<UserInformationResponse> GetCurrentUserInformation();

		/// <summary>
		/// Signs in a user.
		/// </summary>
		/// <param name="login">The login credentials.</param>
		/// <returns>The login result.</returns>
		Task<UserLoginResponse> LoginUser(UserLoginRequest login);

		/// <summary>
		/// Gets the currently signed in user
		/// </summary>
		/// <param name="throwIfNone">Throws an exception if no user is signed in.</param>
		/// <returns>The currently signed in user</returns>
		Task<User> GetCurrentUser(bool throwIfNone = true);

		/// <summary>
		/// Logs out the current user.
		/// </summary>
		/// <returns></returns>
		Task LogoutUser();
	}
}
