namespace AutoKat.Domain.Authentication
{
	public class RefreshTokenResult
	{
		public bool Success { get; set; }

		public AuthenticationData AuthenticationData { get; set; }
	}
}
