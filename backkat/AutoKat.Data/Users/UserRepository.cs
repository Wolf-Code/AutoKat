using AutoKat.Core.Users;
using Microsoft.EntityFrameworkCore;
using System.Threading.Tasks;

namespace AutoKat.Data.Users
{
	public class UserRepository : Repository<User>, IUserRepository
	{
		public UserRepository(AutoKatContext autoKatContext) : base(autoKatContext)
		{
		}

		public async Task<User> FindByEmail(string email)
		{
			var user = await this.Query().FirstOrDefaultAsync(x => x.Email == email.ToLower());

			return user;
		}
	}
}
