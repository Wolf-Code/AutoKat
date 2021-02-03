using AutoKat.Domain.Devices;
using AutoKat.Infrastructure.Devices;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using System.Threading.Tasks;

namespace AutoKat.Controllers
{
	[Route("api/[controller]")]
	[Authorize]
	public class DeviceController : Controller
	{
		private readonly IDeviceService deviceService;

		public DeviceController(IDeviceService deviceService)
		{
			this.deviceService = deviceService;
		}

		[HttpPost]
		public async Task<DeviceRegistrationResult> Register([FromBody] DeviceRegistration registration)
		{
			return await this.deviceService.Register(registration);
		}
	}
}
