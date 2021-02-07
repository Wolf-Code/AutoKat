using System;
using System.Runtime.Serialization;

namespace AutoKat.Services.Authentication.Exceptions
{
	public class InvalidRefreshTokenException : Exception
	{
		public InvalidRefreshTokenException()
		{
		}

		public InvalidRefreshTokenException(string message) : base(message)
		{
		}

		public InvalidRefreshTokenException(string message, Exception innerException) : base(message, innerException)
		{
		}

		protected InvalidRefreshTokenException(SerializationInfo info, StreamingContext context) : base(info, context)
		{
		}
	}
}
