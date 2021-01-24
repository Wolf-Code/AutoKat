using AutoKat.Data.Devices;
using AutoKat.Data.Devices.Entities;
using AutoKat.Data.Logging;
using AutoKat.Data.Logging.Entities;
using AutoKat.Domain.Logging;
using System;
using System.Threading.Tasks;

namespace AutoKat.Infrastructure.Logging
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

		public async Task ProcessNewLog(Guid id, NewLogEntry newLog)
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
