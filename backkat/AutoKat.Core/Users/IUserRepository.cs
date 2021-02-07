using System.Threading.Tasks;

namespace AutoKat.Core.Users
{
	public interface IUserRepository : IRepository<User>
	{
		Task<User> FindByEmail(string email);
	}
}
