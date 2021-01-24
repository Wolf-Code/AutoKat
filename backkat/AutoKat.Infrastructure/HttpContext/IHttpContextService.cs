using AutoKat.Core.DependencyInjection;

namespace AutoKat.Infrastructure.HttpContext
{
	public interface IHttpContextService : IService
	{
		string GetCurrentUserEmail();
	}
}
