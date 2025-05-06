using BirdBoxFull.Shared;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace BirdBoxFull.Server.Data
{
    public class EncomendaConfiguration : IEntityTypeConfiguration<Encomenda>
    {

        public void Configure(EntityTypeBuilder<Encomenda> builder)
        {
          

            builder.HasOne(e => e.Utilizador)
                .WithMany(u => u.Encomendas)
                .HasForeignKey(e => e.UtilizadorUsername)
                .OnDelete(DeleteBehavior.NoAction);

            builder.Property(e => e.codEncomenda).HasDefaultValue("NEWID()");
            // Other configurations...
        }
    }
}
