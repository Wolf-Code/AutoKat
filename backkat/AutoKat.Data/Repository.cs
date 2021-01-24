using AutoKat.Data.Exceptions;
using System.Linq;
using System.Threading.Tasks;

namespace AutoKat.Data
{
	public abstract class Repository<TEntity> : IRepository<TEntity>
		where TEntity : class, new()
	{
		private readonly AutoKatContext autoKatContext;

		public Repository(AutoKatContext autoKatContext)
		{
			this.autoKatContext = autoKatContext;
		}

		public async Task<TEntity> FindById(object id, bool throwIfNotFound = true)
		{
			var result = await this.autoKatContext.FindAsync<TEntity>(id);

			if (result == null)
			{
				throw new EntityNotFoundException<TEntity>($"Unable to find entity of type {typeof(TEntity).Name} with Id {id}");
			}

			return result;
		}

		public async Task<TEntity> Insert(TEntity entity)
		{
			var result = await this.autoKatContext.AddAsync(entity);
			await autoKatContext.SaveChangesAsync();

			return result.Entity;
		}

		protected IQueryable<TEntity> Query()
		{
			return this.autoKatContext.Set<TEntity>();
		}
	}
}
