using AutoKat.Services.Translations;
using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;

namespace AutoKat.Translations
{
	[Route("api/[controller]")]
	public class TranslationsController : Controller
	{
		private readonly ITranslationsService translationsService;

		public TranslationsController(ITranslationsService translationsService)
		{
			this.translationsService = translationsService;
		}

		[HttpGet]
		[Route("{culture}")]
		public Dictionary<string, string> GetTranslations(string culture)
		{
			return translationsService.GetTranslations(culture);
		}
	}
}
