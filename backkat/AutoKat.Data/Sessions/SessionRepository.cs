using AutoKat.Core.Utilities.DateTime;
using AutoKat.Data.Devices.Entities;
using AutoKat.Data.Sessions.Entities;
using AutoKat.Data.Users.Entities;
using Microsoft.EntityFrameworkCore;
using System.Linq;
using System.Net;
using System.Threading.Tasks;

namespace AutoKat.Data.Sessions
{
	public class SessionRepository : Repository<Session>, ISessionRepository
	{
		private readonly IDateTimeProvider dateTimeProvider;

		public SessionRepository(
			AutoKatContext autoKatContext,
			IDateTimeProvider dateTimeProvider
		) : base(autoKatContext)
		{
			this.dateTimeProvider = dateTimeProvider;
		}

		public async Task EndActiveSession(User user, string token, IPAddress ip)
		{
			var activeSession = await this.GetActiveSession(user, token, ip);
			activeSession.SessionEnd = this.dateTimeProvider.NowUtc;
			await this.SaveChanges();
		}

		public async Task<Session> GetActiveSession(User user, string token, IPAddress address)
		{
			var now = this.dateTimeProvider.NowUtc;
			return await (from session in this.Query()
						  where session.User == user
						  where session.Token == token
						  where session.IP == address
						  where session.SessionStart <= now
						  where session.SessionEnd > now
						  select session).SingleOrDefaultAsync();
		}

		public async Task<Session> GetActiveSession(string token, IPAddress address)
		{
			var now = this.dateTimeProvider.NowUtc;
			return await (from session in this.Query().Include(x => x.User).Include(x => x.Device)
						  where session.Token == token
						  where session.IP == address
						  where session.SessionStart <= now
						  where session.SessionEnd > now
						  select session).SingleOrDefaultAsync();
		}

		public async Task<Device> GetDeviceFromRefreshToken(string refreshToken)
		{
			var now = this.dateTimeProvider.NowUtc;
			var activeSession = await (from session in this.Query().Include(x => x.Device)
									   where session.Token == refreshToken
									   where session.SessionStart <= now
									   where session.SessionEnd > now
									   select session).SingleOrDefaultAsync();

			if (activeSession == null)
			{
				return null;
			}

			return activeSession.Device;
		}

		public async Task<User> GetUserFromRefreshToken(string refreshToken)
		{
			var now = this.dateTimeProvider.NowUtc;
			var activeSession = await (from session in this.Query().Include(x => x.User)
									   where session.Token == refreshToken
									   where session.SessionStart <= now
									   where session.SessionEnd > now
									   select session).SingleOrDefaultAsync();

			if (activeSession == null)
			{
				return null;
			}

			return activeSession.User;
		}

		public async Task<Session> StartNewSession(User user, string token, IPAddress ip, double sessionLifetime)
		{
			var now = this.dateTimeProvider.NowUtc;
			return await this.Insert(new Session
			{
				IP = ip,
				SessionStart = now,
				SessionEnd = now.AddSeconds(sessionLifetime),
				Token = token,
				User = user
			});
		}

		public async Task<Session> StartNewSession(Device device, string token, IPAddress ip, double sessionLifetime)
		{
			var now = this.dateTimeProvider.NowUtc;
			return await this.Insert(new Session
			{
				IP = ip,
				SessionStart = now,
				SessionEnd = now.AddSeconds(sessionLifetime),
				Token = token,
				Device = device
			});
		}
	}
}
