using AutoKat.Core.Authentication;

namespace AutoKat.Core.Devices.Registration
{
	public class DeviceRegistrationResponse
	{
		public bool Success { get; set; }

		public AuthenticationData AuthenticationData { get; set; }
	}
}
