using BirdBoxFull.Server.Data;
using BirdBoxFull.Server.Services.ServicoProduto;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using System;
using System.Threading;
using System.Threading.Tasks;

public class AuctionWinnerService : BackgroundService
{
    private readonly IServiceProvider _serviceProvider;

    public AuctionWinnerService(IServiceProvider serviceProvider)
    {
        _serviceProvider = serviceProvider ?? throw new ArgumentNullException(nameof(serviceProvider));
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        while (!stoppingToken.IsCancellationRequested)
        {
            using (var scope = _serviceProvider.CreateScope())
            {
                var dbContext = scope.ServiceProvider.GetRequiredService<DataContext>();
                // Resolve the services you need from the scope
                var auctionService = scope.ServiceProvider.GetRequiredService<IServicoProduto>();
                var otherService = scope.ServiceProvider.GetRequiredService<IServicoLicitacao>();

                // Implement logic to choose winning bids for ended auctions
                await auctionService.ChooseWinningBids();
            }

            await Task.Delay(TimeSpan.FromMinutes(1), stoppingToken); // Adjust the interval as needed
        }
    }
}