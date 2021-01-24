using AutoKat.Data.Devices.Entities;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;

namespace AutoKat.Data
{
	public class AutoKatContext : DbContext
	{
		private static IEnumerable<Type> EntityTypes { get; }

		static AutoKatContext()
		{
			var types = from type in typeof(Device).Assembly.GetTypes()
						where !type.IsAbstract
						where !type.IsInterface
						where typeof(IEntity).IsAssignableFrom(type)
						select type;

			EntityTypes = types.ToList();
		}

		public AutoKatContext(DbContextOptions<AutoKatContext> options) : base(options)
		{

		}

		protected override void OnModelCreating(ModelBuilder modelBuilder)
		{
			foreach (var type in EntityTypes)
			{
				modelBuilder.Entity(type);
			}

			base.OnModelCreating(modelBuilder);
		}
	}
}
