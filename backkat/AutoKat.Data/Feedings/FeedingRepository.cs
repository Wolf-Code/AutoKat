using AutoKat.Data.Feedings.Entities;

namespace AutoKat.Data.Feedings
{
	public class FeedingRepository : Repository<Feeding>, IFeedingRepository
	{
		public FeedingRepository(AutoKatContext autoKatContext) : base(autoKatContext)
		{
		}
	}
}
