using AutoKat.Core.Logging;

namespace AutoKat.Domain.Logging.NewLogEntry
{
	public class NewLogEntryRequest
	{
		public string Message { get; set; }

		public LogSeverity Severity { get; set; }
	}
}
