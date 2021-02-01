using AutoKat.Data.Users.Entities;
using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Net;

namespace AutoKat.Data.Sessions.Entities
{
	public class Session : IEntity
	{
		[Key]
		[DatabaseGenerated(DatabaseGeneratedOption.Identity)]
		public Guid Id { get; set; }

		[Required]
		public User User { get; set; }

		[Required]
		public string Token { get; set; }

		[Required]
		public IPAddress IP { get; set; }

		[Required]
		public DateTime SessionStart { get; set; }

		[Required]
		public DateTime SessionEnd { get; set; }
	}
}
