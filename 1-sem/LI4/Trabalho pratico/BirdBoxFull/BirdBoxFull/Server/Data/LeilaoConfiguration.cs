using BirdBoxFull.Shared;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace BirdBoxFull.Server.Data
{
    public class LeilaoConfiguration : IEntityTypeConfiguration<Leilao>
    {

        public void Configure(EntityTypeBuilder<Leilao> builder)
        {


            builder.Property(e => e.CodLeilao).HasDefaultValue("NEWID()");
            // Other configurations...
        }

    }
}
