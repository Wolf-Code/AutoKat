using AutoKat.Data.Devices.Entities;

namespace AutoKat.Data.Devices
{
	public class DeviceRepository : Repository<Device>, IDeviceRepository
	{
		public DeviceRepository(AutoKatContext autoKatContext) : base(autoKatContext)
		{
		}
	}
}
