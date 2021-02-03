using AutoKat.Data.Devices.Entities;
using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace AutoKat.Data.Feedings.Entities
{
	public class Feeding : IEntity
	{
		[Key]
		[DatabaseGenerated(DatabaseGeneratedOption.Identity)]
		public Guid Id { get; set; }

		[ForeignKey("DeviceId")]
		public Device Device { get; set; }

		public decimal AmountBefore { get; set; }

		public decimal AmountAfter { get; set; }

		public DateTime FeedingStart { get; set; }

		public DateTime FeedingEnd { get; set; }
	}
}
