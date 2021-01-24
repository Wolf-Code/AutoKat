using System;
using System.Runtime.Serialization;

namespace AutoKat.Core.Exceptions
{
	[Serializable]
	public class AutoKatException : Exception
	{
		public AutoKatException()
		{
		}

		public AutoKatException(string message) : base(message)
		{
		}

		public AutoKatException(string message, Exception innerException) : base(message, innerException)
		{
		}

		protected AutoKatException(SerializationInfo info, StreamingContext context) : base(info, context)
		{
		}
	}
}
