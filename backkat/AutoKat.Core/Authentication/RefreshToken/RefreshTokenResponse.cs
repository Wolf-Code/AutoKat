namespace AutoKat.Core.Authentication.RefreshToken
{
	public class RefreshTokenResponse
	{
		public bool Success { get; set; }

		public AuthenticationData AuthenticationData { get; set; }
	}
}
