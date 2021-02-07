using AutoKat.Core.Devices;
using System;

namespace AutoKat.Core.Feedings
{
	public class Feeding : IEntity
	{
		public Guid Id { get; set; }

		public Device Device { get; set; }

		public decimal AmountBefore { get; set; }

		public decimal AmountAfter { get; set; }

		public DateTime FeedingStart { get; set; }

		public DateTime FeedingEnd { get; set; }
	}
}
