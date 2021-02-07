using AutoKat.Core.Feedings;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace AutoKat.Data.Feedings
{
	public class FeedingMapping : IEntityTypeConfiguration<Feeding>
	{
		public void Configure(EntityTypeBuilder<Feeding> builder)
		{
			builder.HasKey(x => x.Id);

			builder.HasOne(x => x.Device).WithMany();
		}
	}
}
