using AutoKat.Data.Devices.Entities;
using AutoKat.Domain.Logging;
using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace AutoKat.Data.Logging.Entities
{
	public class LogEntry : IEntity
	{
		[Key]
		[DatabaseGenerated(DatabaseGeneratedOption.Identity)]
		public Guid Id { get; set; }

		[ForeignKey("DeviceId")]
		public Device Device { get; set; }

		[Required]
		public LogSeverity Severity { get; set; }

		[Required]
		public string Log { get; set; }

		public string Exception { get; set; }
	}
}
