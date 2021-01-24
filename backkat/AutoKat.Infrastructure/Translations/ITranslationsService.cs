using AutoKat.Core.DependencyInjection;
using System.Collections.Generic;

namespace AutoKat.Infrastructure.Translations
{
	public interface ITranslationsService : ITransientService
	{
		Dictionary<string, string> GetTranslations(string culture);
	}
}