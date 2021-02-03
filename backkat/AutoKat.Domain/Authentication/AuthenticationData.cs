namespace AutoKat.Domain.Authentication
{
	public class AuthenticationData
	{
		public string RefreshToken { get; set; }
		public string Token { get; set; }
		public long TokenExpirationTime { get; set; }
		public string Id { get; set; }
	}
}
