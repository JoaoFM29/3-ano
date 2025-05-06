using BirdBoxFull.Client;
using BirdBoxFull.Client.Services.ServicoProduto;
using Blazored.LocalStorage;
using Microsoft.AspNetCore.Components.Web;
using Microsoft.AspNetCore.Components.WebAssembly.Hosting;

var builder = WebAssemblyHostBuilder.CreateDefault(args);
builder.RootComponents.Add<App>("#app");
builder.RootComponents.Add<HeadOutlet>("head::after");

builder.Services.AddScoped(sp => new HttpClient { BaseAddress = new Uri(builder.HostEnvironment.BaseAddress) });
builder.Services.AddScoped<IServicoProduto, ServicoProduto>();
builder.Services.AddScoped<IServicoUtilizador, ServicoUtilizador>();
builder.Services.AddScoped<IServicoLicitacao, ServicoLicitacao>();
builder.Services.AddScoped<IServicoEncomenda, ServicoEncomenda>();
builder.Services.AddBlazoredLocalStorage();

await builder.Build().RunAsync();
