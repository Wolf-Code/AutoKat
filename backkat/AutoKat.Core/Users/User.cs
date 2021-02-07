namespace AutoKat.Core.Users
{
	public class User : IEntity
	{
		public int Id { get; set; }

		public string Email { get; set; }

		public string Password { get; set; }

		public byte[] Salt { get; set; }

		public UserPreferences Preferences { get; set; }
	}
}
