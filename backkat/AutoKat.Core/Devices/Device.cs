using AutoKat.Core.Users;
using System;

namespace AutoKat.Core.Devices
{
	public class Device : IEntity
	{
		public Guid Id { get; set; }

		public User User { get; set; }

		public int UserId { get; set; }

		public string MacAddress { get; set; }

		public string Name { get; set; }
	}
}
