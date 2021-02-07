using AutoKat.Core.Devices;
using AutoKat.Core.Users;
using System.Net;
using System.Threading.Tasks;

namespace AutoKat.Core.Sessions
{
	public interface ISessionRepository : IRepository<Session>
	{
		Task<Session> GetActiveSession(User user, string token, IPAddress address);
		Task<Session> GetActiveSession(string token, IPAddress address);
		Task<Session> StartNewSession(User user, string token, IPAddress ip, double sessionLifetime);
		Task<Session> StartNewSession(Device device, string token, IPAddress ip, double sessionLifetime);
		Task EndActiveSession(User user, string token, IPAddress ip);
		Task<User> GetUserFromRefreshToken(string refreshToken);
		Task<Device> GetDeviceFromRefreshToken(string refreshToken);
	}
}