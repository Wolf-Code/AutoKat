namespace AutoKat.Core.Utilities.DateTime
{
	public class DateTimeProvider : IDateTimeProvider
	{
		public System.DateTime NowUtc => System.DateTime.UtcNow;
	}
}
