using AutoKat.Core.DependencyInjection;
using System.Threading.Tasks;

namespace AutoKat.Data
{
	public interface IRepository<T> : IRepository
		where T : class, new()
	{
		Task<T> Insert(T entity);

		Task<T> FindById(object id, bool throwIfNotFound = true);

		Task SaveChanges();
	}
}
