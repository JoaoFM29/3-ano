global using Microsoft.EntityFrameworkCore;
using BirdBoxFull.Server.Data;
using BirdBoxFull.Server.Services.ServicoProduto;
using Microsoft.AspNetCore.ResponseCompression;
using Microsoft.Extensions.FileProviders;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddDbContext<DataContext>(options => options.UseSqlServer(builder.Configuration.GetConnectionString("DefaultConnection")));
builder.Services.AddControllersWithViews();


builder.Services.AddRazorPages();
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

builder.Services.AddScoped<IServicoProduto,ServicoProduto>();
builder.Services.AddScoped<IServicoUtilizador,ServicoUtilizador>();
builder.Services.AddScoped<IPagamentos, Pagamentos>();
builder.Services.AddScoped<IServicoLicitacao, ServicoLicitacao>();
builder.Services.AddScoped<IServicoEncomenda, ServicoEncomenda>();
builder.Services.AddScoped<IEmailSenderService, EmailSenderService>();


builder.Services.AddHostedService<AuctionWinnerService>();
builder.Services.AddHostedService<DatabaseBackupService>();

var app = builder.Build();
app.UseSwaggerUI();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseWebAssemblyDebugging();
}
else
{
    app.UseExceptionHandler("/Error");
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}


app.UseSwagger();
app.UseHttpsRedirection();

app.UseBlazorFrameworkFiles();
app.UseStaticFiles();

app.UseStaticFiles(new StaticFileOptions
{
    FileProvider = new PhysicalFileProvider(Path.Combine(Directory.GetCurrentDirectory(), "NovaPasta")),
    RequestPath = "/NovaPasta" // Serve files from the /files path
});


app.UseRouting();


app.MapRazorPages();
app.MapControllers();
app.MapFallbackToFile("index.html");

app.Run();
