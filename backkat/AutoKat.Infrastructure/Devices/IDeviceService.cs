using AutoKat.Core.DependencyInjection;
using AutoKat.Domain.Devices;
using System.Threading.Tasks;

namespace AutoKat.Infrastructure.Devices
{
	public interface IDeviceService : IService
	{
		Task<DeviceRegistrationResult> Register(DeviceRegistration registration);
	}
}