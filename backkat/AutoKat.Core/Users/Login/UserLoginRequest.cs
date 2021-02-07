namespace AutoKat.Core.Users.Login
{
	public class UserLoginRequest
	{
		public string Email { get; set; }

		public string Password { get; set; }

		public bool RememberMe { get; set; }
	}
}
