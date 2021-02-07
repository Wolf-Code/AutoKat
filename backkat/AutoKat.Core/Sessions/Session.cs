using AutoKat.Core.Devices;
using AutoKat.Core.Users;
using System;
using System.ComponentModel.DataAnnotations;
using System.Net;

namespace AutoKat.Core.Sessions
{
	public class Session : IEntity
	{
		public Guid Id { get; set; }

		public User User { get; set; }

		public Device Device { get; set; }

		public string Token { get; set; }

		public IPAddress IP { get; set; }

		public DateTime SessionStart { get; set; }

		[Required]
		public DateTime SessionEnd { get; set; }
	}
}
