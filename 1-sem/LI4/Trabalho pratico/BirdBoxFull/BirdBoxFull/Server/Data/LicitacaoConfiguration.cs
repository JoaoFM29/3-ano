using BirdBoxFull.Shared;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace BirdBoxFull.Server.Data
{
    public class LicitacaoConfiguration : IEntityTypeConfiguration<Licitacao>
    {
        public void Configure(EntityTypeBuilder<Licitacao> builder)
        {
            // Other configurations...

            builder.HasOne(l => l.Utilizador)
                .WithMany(u => u.Licitacoes)
                .HasForeignKey(l => l.UtilizadorUsername)
                .OnDelete(DeleteBehavior.NoAction);  // Specify ON DELETE NO ACTION here

            builder.HasOne(l => l.Leilao)
                .WithMany(u => u.Licitacoes)
                .HasForeignKey(l => l.LeilaoCodLeilao)
                .OnDelete(DeleteBehavior.NoAction);  // Specify the appropriate behavior for Leilao relationship

            builder.Property(e => e.codLicitacao).HasDefaultValue("NEWID()");

            // Other configurations...
        }
    }

}
