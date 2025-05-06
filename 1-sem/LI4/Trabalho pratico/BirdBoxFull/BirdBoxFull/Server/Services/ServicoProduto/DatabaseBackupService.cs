using System;
using System.IO;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using BirdBoxFull.Server.Data;

namespace BirdBoxFull.Server.Services.ServicoProduto
{
    public class DatabaseBackupService : BackgroundService
    {
        private readonly IServiceProvider _services;

        public DatabaseBackupService(IServiceProvider services)
        {
            _services = services ?? throw new ArgumentNullException(nameof(services));
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            while (!stoppingToken.IsCancellationRequested)
            {
                if (DateTime.Now.Hour == 4)
                {
                    using (var scope = _services.CreateScope())
                    {
                        var dbContext = scope.ServiceProvider.GetRequiredService<DataContext>();
                        await PerformBackup(dbContext);
                    }
                }

                await Task.Delay(TimeSpan.FromHours(24), stoppingToken); // Adjust the interval as needed
            }
        }

        private async Task PerformBackup(DataContext dbContext)
        {
            try
            {
                string backupFolderPath = "D:\\LI4VersaoComServer\\BirdBoxFull\\BirdBoxFull\\Server\\Backup\\"; // Provide the desired backup folder path
                string backupFileName = $"database_backup_{DateTime.Now:yyyyMMdd_HHmmss}.bak";
                string backupFilePath = Path.Combine(backupFolderPath, backupFileName);

                await dbContext.Database.ExecuteSqlRawAsync($"BACKUP DATABASE li TO DISK = '{backupFilePath}' WITH FORMAT");

                Console.WriteLine($"Database backup created at: {backupFilePath}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error creating database backup: {ex.Message}");
            }
        }
    }
}
