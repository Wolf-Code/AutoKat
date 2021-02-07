﻿using AutoKat.Core;
using AutoKat.Core.Devices;
using AutoKat.Data.Devices;
using AutoKat.Data.Feedings;
using AutoKat.Data.Sessions;
using AutoKat.Data.Users;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
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
			modelBuilder.ApplyConfiguration(new DeviceMapping());
			modelBuilder.ApplyConfiguration(new FeedingMapping());
			modelBuilder.ApplyConfiguration(new SessionMapping());
			modelBuilder.ApplyConfiguration(new UserMapping());

			var dateTimeConverter = new ValueConverter<DateTime, DateTime>(v => v, v => DateTime.SpecifyKind(v, DateTimeKind.Utc));

			foreach (var entityType in modelBuilder.Model.GetEntityTypes())
			{
				foreach (var property in entityType.GetProperties())
				{
					if (property.ClrType == typeof(DateTime) || property.ClrType == typeof(DateTime?))
					{
						property.SetValueConverter(dateTimeConverter);
					}
				}
			}

			base.OnModelCreating(modelBuilder);
		}
	}
}
