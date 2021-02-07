using AutoKat.Core.Authentication;
using AutoKat.Core.Devices;
using AutoKat.Core.Users;
using System.Threading.Tasks;

namespace AutoKat.Services.Authentication
{
	public interface IAuthenticationService
	{
		int JwtLifespan { get; }

		AuthenticationData GetAuthenticationData(User user, string refreshToken);

		AuthenticationData GetAuthenticationData(Device device, string refreshToken);

		Task<AuthenticationData> GetNewUserToken(string refreshToken);

		Task<AuthenticationData> GetNewDeviceToken(string refreshToken);
		Task<AuthenticationData> GetNewToken(string refreshToken);

		Task<bool> ValidateTokenWithSession(string token, User use);
	}
}
