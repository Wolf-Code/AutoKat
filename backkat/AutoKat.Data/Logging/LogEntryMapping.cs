using AutoKat.Core.Logging;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace AutoKat.Data.Logging
{
	public class LogEntryMapping : IEntityTypeConfiguration<LogEntry>
	{
		public void Configure(EntityTypeBuilder<LogEntry> builder)
		{
			builder.HasKey(x => x.Id);

			builder.HasOne(x => x.Device).WithMany().IsRequired();

			builder.Property(x => x.Log).IsRequired();
			builder.Property(x => x.Severity).IsRequired();
		}
	}
}
