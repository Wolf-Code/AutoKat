namespace AutoKat.Domain.Users
{
	public class UserRegistrationResult
	{
		public UserRegistrationResult(string error)
		{
			this.Information = error;
		}

		public UserRegistrationResult(UserAuthenticationData authenticationData)
		{
			this.AuthenticationData = authenticationData;
			this.Success = true;
		}

		public bool Success { get; set; }

		public string Information { get; set; }

		public UserAuthenticationData AuthenticationData { get; set; }
	}
}
