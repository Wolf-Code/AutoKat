using AutoKat.Domain.Users;

namespace AutoKat.Infrastructure.Authentication
{
	public interface IAuthenticationService
	{
		UserAuthenticationData GetAuthenticationData(string email);
	}
}
