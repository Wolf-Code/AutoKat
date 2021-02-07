using AutoKat.Core.Users;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace AutoKat.Data.Users
{
	public class UserMapping : IEntityTypeConfiguration<User>
	{
		public void Configure(EntityTypeBuilder<User> builder)
		{
			builder.HasKey(x => x.Id);

			builder
				.Property(x => x.Preferences)
				.HasColumnType("jsonb");

			builder
				.Property(x => x.Password)
				.HasMaxLength(128)
				.IsRequired();

			builder
				.Property(x => x.Email)
				.IsRequired();

			builder
				.Property(x => x.Salt)
				.IsRequired();
		}
	}
}
