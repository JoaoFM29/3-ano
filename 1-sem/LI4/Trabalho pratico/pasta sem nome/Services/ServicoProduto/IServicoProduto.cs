using BirdBoxFull.Shared;
using Microsoft.AspNetCore.Http;
using static System.Net.WebRequestMethods;

namespace BirdBoxFull.Client.Services.ServicoProduto
{
	public interface IServicoProduto
	{
		List<Leilao> Leiloes { get; set; }
		Task loadLeiloes();
        Task<Leilao> loadLeilao(string cod);

		Task UploadImages(List<LeilaoImage> images);

        Task AddLeilao(Leilao novoLeilao);

		Task<List<Leilao>> GetLeilaoByUser(string Username);

		Task UpdateLeilaoRelatorio(string codLeilao, string fileName, byte[] data);

        Task<bool> AddLeilaoWishList(string Leilao, string username);

        Task<List<WishList>> GetLeilaoWishList(string username);
		Task RemoveLeilao(string codLeilao);
    }
}
