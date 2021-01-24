using AutoKat.Domain.Logging;
using System;
using System.Threading.Tasks;

namespace AutoKat.Infrastructure.Logging
{
	public interface ILoggingService
	{
		Task ProcessNewLog(Guid id, NewLogEntry newLog);
	}
}
