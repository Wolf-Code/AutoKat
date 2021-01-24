namespace AutoKat.Domain.Users
{
	public class UserAuthenticationData
	{
		public string Token { get; set; }
		public long TokenExpirationTime { get; set; }
		public string Id { get; set; }
	}
}
