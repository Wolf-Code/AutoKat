using AutoKat.Core.Exceptions;

namespace AutoKat.Infrastructure.Users.Exceptions
{
	public class EmailAlreadyInUseException : AutoKatException
	{
		public EmailAlreadyInUseException(string message) : base(message)
		{
		}
	}
}
