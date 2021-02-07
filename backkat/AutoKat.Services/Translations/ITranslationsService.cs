using AutoKat.Core.DependencyInjection;
using System.Collections.Generic;

namespace AutoKat.Services.Translations
{
	public interface ITranslationsService : ITransientService
	{
		Dictionary<string, string> GetTranslations(string culture);
	}
}