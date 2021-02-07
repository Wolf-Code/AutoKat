using AutoKat.Domain.Logging.NewLogEntry;
using System;
using System.Threading.Tasks;

namespace AutoKat.Services.Logging
{
	public interface ILoggingService
	{
		Task ProcessNewLog(Guid id, NewLogEntryRequest newLog);
	}
}
