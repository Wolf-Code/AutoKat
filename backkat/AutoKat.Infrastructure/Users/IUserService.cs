using AutoKat.Core.DependencyInjection;
using AutoKat.Data.Users.Entities;
using AutoKat.Domain.Users;
using System.Threading.Tasks;

namespace AutoKat.Infrastructure.Users
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
		Task<UserRegistrationResult> RegisterUser(UserRegistration newUser);

		/// <summary>
		/// Returns the current user's information.
		/// </summary>
		/// <returns>The current user's information</returns>
		Task<UserInformationResult> GetCurrentUserInformation();

		/// <summary>
		/// Signs in a user.
		/// </summary>
		/// <param name="login">The login credentials.</param>
		/// <returns>The login result.</returns>
		Task<UserLoginResult> LoginUser(UserLogin login);

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
