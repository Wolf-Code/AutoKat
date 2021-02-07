using AutoKat.Core.Exceptions;

namespace AutoKat.Services.Users.Exceptions
{
	public class EmailAlreadyInUseException : AutoKatException
	{
		public EmailAlreadyInUseException(string message) : base(message)
		{
		}
	}
}
