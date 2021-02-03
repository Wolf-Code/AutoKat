using AutoKat.Data.Users.Entities;
using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace AutoKat.Data.Devices.Entities
{
	public class Device : IEntity
	{
		[Key]
		[DatabaseGenerated(DatabaseGeneratedOption.Identity)]
		public Guid Id { get; set; }

		[ForeignKey("UserId")]
		public User User { get; set; }

		public string MacAddress { get; set; }

		public string Name { get; set; }
	}
}
