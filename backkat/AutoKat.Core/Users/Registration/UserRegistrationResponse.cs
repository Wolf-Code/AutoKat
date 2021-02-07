namespace AutoKat.Core.Users.Registration
{
	public class UserRegistrationResponse
	{
		public UserRegistrationResponse(string error)
		{
			this.Information = error;
		}

		public UserRegistrationResponse()
		{
			this.Success = true;
		}

		public bool Success { get; set; }

		public string Information { get; set; }
	}
}
