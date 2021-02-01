using AutoKat.Data.Sessions.Entities;
using AutoKat.Data.Users.Entities;
using System.Net;
using System.Threading.Tasks;

namespace AutoKat.Data.Sessions
{
	public interface ISessionRepository : IRepository<Session>
	{
		Task<Session> GetActiveSession(User user, string token, IPAddress address);
		Task<Session> StartNewSession(User user, string token, IPAddress ip, int sessionLifetime);
		Task EndActiveSession(User user, string token, IPAddress ip);
	}
}