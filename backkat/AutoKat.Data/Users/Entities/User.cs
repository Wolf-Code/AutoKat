using AutoKat.Domain.Users;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace AutoKat.Data.Users.Entities
{
	public class User : IEntity
	{
		[Key]
		[DatabaseGenerated(DatabaseGeneratedOption.Identity)]
		public int Id { get; set; }

		[Required]
		public string Email { get; set; }

		[MaxLength(128)]
		[Required]
		public string Password { get; set; }

		[Required]
		public byte[] Salt { get; set; }

		[Column(TypeName = "jsonb")]
		public UserPreferences Preferences { get; set; }
	}
}
