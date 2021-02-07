using AutoKat.Core.Devices;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace AutoKat.Data.Devices
{
	public class DeviceMapping : IEntityTypeConfiguration<Device>
	{
		public void Configure(EntityTypeBuilder<Device> builder)
		{
			builder.HasKey(x => x.Id);
			builder.Property(x => x.MacAddress).IsRequired(true);
			builder.Property(x => x.Name).IsRequired(true);
			builder.HasOne(x => x.User).WithMany();
			//builder
			//	.Property(x => x.User)
			//	.HasColumnName("UserId")
			//	.IsRequired(true);
		}
	}
}
