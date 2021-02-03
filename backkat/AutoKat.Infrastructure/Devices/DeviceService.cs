using AutoKat.Core.Utilities.DateTime;
using AutoKat.Data.Devices;
using AutoKat.Data.Devices.Entities;
using AutoKat.Data.Sessions;
using AutoKat.Domain.Authentication;
using AutoKat.Domain.Devices;
using AutoKat.Infrastructure.Authentication;
using AutoKat.Infrastructure.HttpContext;
using AutoKat.Infrastructure.Users;
using System;
using System.Threading.Tasks;

namespace AutoKat.Infrastructure.Devices
{
	public class DeviceService : IDeviceService
	{
		private readonly IAuthenticationService authenticationService;
		private readonly IDateTimeProvider dateTimeProvider;
		private readonly IDeviceRepository deviceRepository;
		private readonly ISessionRepository sessionRepository;
		private readonly IHttpContextService httpContextService;
		private readonly IUserService userService;

		public DeviceService(
			IAuthenticationService authenticationService,
			IDateTimeProvider dateTimeProvider,
			IDeviceRepository deviceRepository,
			ISessionRepository sessionRepository,
			IHttpContextService httpContextService,
			IUserService userService
		)
		{
			this.authenticationService = authenticationService;
			this.dateTimeProvider = dateTimeProvider;
			this.deviceRepository = deviceRepository;
			this.sessionRepository = sessionRepository;
			this.httpContextService = httpContextService;
			this.userService = userService;
		}

		public async Task<DeviceRegistrationResult> Register(DeviceRegistration registration)
		{
			Device device = null;
			try
			{
				var user = await this.userService.GetCurrentUser();
				device = await this.deviceRepository.Insert(new Device
				{
					User = user,
					Name = "Autokat",
					MacAddress = registration.MacAddress
				});

				var tokens = await this.GetTokens(device);
				return new DeviceRegistrationResult
				{
					AuthenticationData = tokens,
					Success = true
				};
			}
			catch
			{
				if (device == null)
				{
					throw;
				}

				await this.deviceRepository.Delete(device);
				throw;
			}
		}

		private async Task<AuthenticationData> GetTokens(Device device)
		{
			var refreshToken = this.authenticationService.GetAuthenticationData(device, null);
			var token = this.authenticationService.GetAuthenticationData(device, refreshToken.Token);
			token.RefreshToken = refreshToken.Token;

			var ip = this.httpContextService.GetCurrentUserIpAddress();
			var now = this.dateTimeProvider.NowUtc;
			var duration = DateTimeOffset.FromUnixTimeSeconds(refreshToken.TokenExpirationTime).UtcDateTime - now;
			await this.sessionRepository.StartNewSession(device, refreshToken.Token, ip, duration.TotalSeconds);

			return new AuthenticationData
			{
				Token = token.Token,
				Id = token.Id,
				TokenExpirationTime = token.TokenExpirationTime,
				RefreshToken = refreshToken.Token
			};
		}
	}
}
