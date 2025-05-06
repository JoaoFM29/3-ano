using BirdBoxFull.Shared;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Hosting;

namespace BirdBoxFull.Server.Data
{
    public class DataContext : DbContext
    {
        public DataContext(DbContextOptions<DataContext> options) : base(options)
        {
            
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.ApplyConfiguration(new LeilaoConfiguration());
            modelBuilder.ApplyConfiguration(new LicitacaoConfiguration());
            modelBuilder.ApplyConfiguration(new EncomendaConfiguration());
            modelBuilder.ApplyConfiguration(new WishListConfiguration());

            base.OnModelCreating(modelBuilder);
        }


        public DbSet<Utilizador> Utilizadores { get; set; }

        public DbSet<Leilao> Leiloes { get; set;}

        public DbSet<LeilaoImage> LeilaoImages { get; set; }

        public DbSet<Licitacao> Licitacoes { get; set; }

        public DbSet<Encomenda> Encomendas { get; set; }

        public DbSet<WishList> WishLists { get; set;}
        

        // protected override void OnModelCreating(ModelBuilder modelBuilder)
        // {
        //    modelBuilder.Entity<Leilao>.HasData();
        //}

    }
}
