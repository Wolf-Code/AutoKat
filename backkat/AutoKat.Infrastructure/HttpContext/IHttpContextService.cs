using AutoKat.Core.DependencyInjection;
using System.Net;

namespace AutoKat.Infrastructure.HttpContext
{
	public interface IHttpContextService : IService
	{
		string GetCookieRefreshToken();

		string GetHeaderToken();

		string GetCurrentUserEmail();

		IPAddress GetCurrentUserIpAddress();
	}
}
