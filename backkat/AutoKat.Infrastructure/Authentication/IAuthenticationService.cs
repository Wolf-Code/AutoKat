using AutoKat.Data.Users.Entities;
using AutoKat.Domain.Users;
using System.Threading.Tasks;

namespace AutoKat.Infrastructure.Authentication
{
	public interface IAuthenticationService
	{
		int JwtLifespan { get; }

		UserAuthenticationData GetAuthenticationData(string email);

		Task<bool> ValidateTokenWithSession(string token, User use);
	}
}
