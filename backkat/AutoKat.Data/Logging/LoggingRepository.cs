using AutoKat.Data.Logging.Entities;

namespace AutoKat.Data.Logging
{
	public class LoggingRepository : Repository<LogEntry>, ILoggingRepository
	{
		public LoggingRepository(AutoKatContext autoKatContext) : base(autoKatContext)
		{
		}
	}
}
