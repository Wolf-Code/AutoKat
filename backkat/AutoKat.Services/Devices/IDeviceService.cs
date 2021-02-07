using AutoKat.Core.DependencyInjection;
using AutoKat.Core.Devices.Registration;
using System.Threading.Tasks;

namespace AutoKat.Services.Devices
{
	public interface IDeviceService : IService
	{
		Task<DeviceRegistrationResponse> Register(DeviceRegistrationRequest registration);
	}
}