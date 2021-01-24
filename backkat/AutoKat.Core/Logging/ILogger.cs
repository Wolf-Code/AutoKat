using AutoKat.Core.DependencyInjection;
using System;

namespace AutoKat.Core.Logging
{
	public interface ILogger : ITransientService
	{
		void Debug(string message);

		void Error(string message, Exception exception);
	}
}
