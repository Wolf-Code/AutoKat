using AutoKat.Data.Users.Entities;
using System.Threading.Tasks;

namespace AutoKat.Data.Users
{
	public interface IUserRepository : IRepository<User>
	{
		Task<User> FindByEmail(string email);
	}
}
