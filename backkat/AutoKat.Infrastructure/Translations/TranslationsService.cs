using AutoKat.Domain.Translations;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Resources;
using System.Threading;

namespace AutoKat.Infrastructure.Translations
{
	public class TranslationsService : ITranslationsService
	{
		static readonly Dictionary<string, PropertyInfo> translationProperties;

		static TranslationsService()
		{
			var assembly = typeof(TranslationCollection).Assembly;
			var types = from type in assembly.GetTypes()
						where type.GetProperties().Any(x => x.PropertyType == typeof(ResourceManager))
						select type;

			translationProperties = new Dictionary<string, PropertyInfo>();

			foreach (var type in types)
			{
				var properties = type
					.GetProperties(BindingFlags.Static | BindingFlags.Public)
					.Where(x => x.PropertyType == typeof(string));

				foreach (var property in properties)
				{
					translationProperties.Add($"{type.Name}.{property.Name}", property);
				}
			}
		}

		public Dictionary<string, string> GetTranslations(string culture)
		{
			var currentCulture = Thread.CurrentThread.CurrentUICulture;
			try
			{
				Thread.CurrentThread.CurrentUICulture = new System.Globalization.CultureInfo(culture);
				var values = new Dictionary<string, string>();

				foreach (var pair in translationProperties)
				{
					values.Add(pair.Key, pair.Value.GetValue(null) as string);
				}

				return values;
			}
			finally
			{
				Thread.CurrentThread.CurrentUICulture = currentCulture;
			}
		}
	}
}
