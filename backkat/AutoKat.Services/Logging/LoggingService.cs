using AutoKat.Core.Devices;
using AutoKat.Core.Logging;
using AutoKat.Domain.Logging.NewLogEntry;
using System;
using System.Threading.Tasks;

namespace AutoKat.Services.Logging
{
	public class LoggingService : ILoggingService
	{
		private readonly ILoggingRepository loggingRepository;
		private readonly IDeviceRepository deviceRepository;

		public LoggingService(
			ILoggingRepository loggingRepository,
			IDeviceRepository deviceRepository
		)
		{
			this.loggingRepository = loggingRepository;
			this.deviceRepository = deviceRepository;
		}

		public async Task ProcessNewLog(Guid id, NewLogEntryRequest newLog)
		{
			var log = new LogEntry
			{
				Device = new Device
				{
					Id = id
				},
				Log = newLog.Message,
				Severity = newLog.Severity
			};

			await this.loggingRepository.Insert(log);
		}
	}
}
