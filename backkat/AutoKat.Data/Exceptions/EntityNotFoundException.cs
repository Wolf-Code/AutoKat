using AutoKat.Core.Exceptions;
using System;
using System.Runtime.Serialization;

namespace AutoKat.Data.Exceptions
{
	[Serializable]
	public class EntityNotFoundException<TEntity> : AutoKatException
	{
		public EntityNotFoundException()
		{
		}

		public EntityNotFoundException(string message) : base(message)
		{
		}

		public EntityNotFoundException(string message, Exception innerException) : base(message, innerException)
		{
		}

		protected EntityNotFoundException(SerializationInfo info, StreamingContext context) : base(info, context)
		{
		}
	}
}
