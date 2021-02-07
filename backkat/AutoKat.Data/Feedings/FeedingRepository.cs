using AutoKat.Core.Feedings;

namespace AutoKat.Data.Feedings
{
	public class FeedingRepository : Repository<Feeding>, IFeedingRepository
	{
		public FeedingRepository(AutoKatContext autoKatContext) : base(autoKatContext)
		{
		}
	}
}
