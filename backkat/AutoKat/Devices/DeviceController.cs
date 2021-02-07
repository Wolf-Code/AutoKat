using AutoKat.Core.Devices.Registration;
using AutoKat.Services.Devices;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System.Threading.Tasks;

namespace AutoKat.Devices
{
	[Route("api/[controller]")]
	[Authorize]
	public class DeviceController : Controller
	{
		private readonly IDeviceService deviceService;
		private readonly ILogger logger;

		public DeviceController(
			IDeviceService deviceService,
			ILogger<DeviceController> logger
		)
		{
			this.deviceService = deviceService;
			this.logger = logger;
		}

		[HttpPost]
		public async Task<DeviceRegistrationResponse> Register([FromBody] DeviceRegistrationRequest registration)
		{
			return await this.deviceService.Register(registration);
		}

		[HttpGet]
		public void Test()
		{
			this.logger.LogDebug("Test");
		}
	}
}
