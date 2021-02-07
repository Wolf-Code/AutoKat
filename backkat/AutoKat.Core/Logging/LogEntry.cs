using AutoKat.Core.Devices;
using System;

namespace AutoKat.Core.Logging
{
	public class LogEntry : IEntity
	{
		public Guid Id { get; set; }

		public Device Device { get; set; }

		public LogSeverity Severity { get; set; }

		public string Log { get; set; }

		public string Exception { get; set; }
	}
}
