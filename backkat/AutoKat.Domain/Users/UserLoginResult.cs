namespace AutoKat.Domain.Users
{
	public class UserLoginResult
	{
		public UserLoginResult(string information)
		{
			this.Information = information;
		}

		public UserLoginResult(UserAuthenticationData authenticationData)
		{
			this.Success = true;
			this.AuthenticationData = authenticationData;
		}

		public bool Success { get; set; }

		public string Information { get; set; }

		public UserAuthenticationData AuthenticationData { get; set; }
	}
}
