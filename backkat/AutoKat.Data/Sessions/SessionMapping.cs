using AutoKat.Core.Sessions;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace AutoKat.Data.Sessions
{
	public class SessionMapping : IEntityTypeConfiguration<Session>
	{
		public void Configure(EntityTypeBuilder<Session> builder)
		{
			builder.HasKey(x => x.Id);

			builder.HasOne(x => x.Device).WithMany();

			builder.HasOne(x => x.User).WithMany();

			builder
				.Property(x => x.SessionStart)
				.IsRequired();

			builder
				.Property(x => x.IP)
				.IsRequired();

			builder
				.Property(x => x.Token)
				.IsRequired();

		}
	}
}
