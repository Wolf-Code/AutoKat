using AutoKat.Domain.Authentication;

namespace AutoKat.Domain.Devices
{
	public class DeviceRegistrationResult
	{
		public bool Success { get; set; }

		public AuthenticationData AuthenticationData { get; set; }
	}
}
