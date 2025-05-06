using BirdBoxFull.Shared;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace BirdBoxFull.Server.Data
{
    public class WishListConfiguration : IEntityTypeConfiguration<WishList>
    {
        public void Configure(EntityTypeBuilder<WishList> builder)
        {
            // Other configurations...

            builder.HasOne(l => l.Utilizador)
                .WithMany(u => u.WishLists)
                .HasForeignKey(l => l.UtilizadorUsername)
                .OnDelete(DeleteBehavior.NoAction);  // Specify ON DELETE NO ACTION here

            builder.HasOne(l => l.Leilao)
                .WithMany(u => u.WishLists)
                .HasForeignKey(l => l.LeilaoCodLeilao)
                .OnDelete(DeleteBehavior.NoAction);  // Specify the appropriate behavior for Leilao relationship

            builder.HasKey(wl => new { wl.LeilaoCodLeilao, wl.UtilizadorUsername });
        }
    }
 }
