using System.Text.Json.Serialization;

namespace AutoKat.Domain.Users
{
	public enum FeedingNotificationPreference
	{
		Never,
		Daily,
		Always
	}

	public class UserPreferences
	{
		[JsonConverter(typeof(JsonStringEnumConverter))]
		public FeedingNotificationPreference FeedingNotificationPreference { get; set; }

		public string Language { get; set; } = "en-US";
	}
}
