using AutoKat.Core.DependencyInjection;
using System.Net;

namespace AutoKat.Infrastructure.HttpContext
{
	public interface IHttpContextService : IService
	{
		string GetToken();

		string GetCurrentUserEmail();

		IPAddress GetCurrentUserIpAddress();
	}
}
