using AutoKat.Core.Authentication;

namespace AutoKat.Core.Users.Login
{
	public class UserLoginResponse
	{
		public UserLoginResponse(string information)
		{
			this.Information = information;
		}

		public UserLoginResponse(AuthenticationData authenticationData)
		{
			this.Success = true;
			this.AuthenticationData = authenticationData;
		}

		public bool Success { get; set; }

		public string Information { get; set; }

		public AuthenticationData AuthenticationData { get; set; }
	}
}
