using AutoKat.Core.DependencyInjection;

namespace AutoKat.Core.Utilities.DateTime
{
	public interface IDateTimeProvider : IService
	{
		System.DateTime NowUtc { get; }
	}
}