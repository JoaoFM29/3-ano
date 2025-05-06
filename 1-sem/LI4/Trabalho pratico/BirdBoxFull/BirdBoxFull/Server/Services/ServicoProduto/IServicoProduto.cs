using BirdBoxFull.Shared;

namespace BirdBoxFull.Server.Services.ServicoProduto
{
    public interface IServicoProduto
    {
        Task<List<Leilao>> GetAllLeiloes();
        Task<List<Leilao>> GetLeilaoByFiltro(List<string> filtros);
        Task<Leilao> GetLeilao(string codLeilao);
        Task UploadImages(List<LeilaoImage> images);
        Task AddLeilao(Leilao novoLeilao);
		Task<List<Leilao>> GetLeilaoByUser(string Username);
        Task ChooseWinningBids();
        Task UpdateLeilaoState(Leilao leilao, string newState);
        Task UpdateLeilaoStateById(string codLeilao, string newState);
        Task ChooseWinningBid(string codLeilao);
        Task UpdateLeilaoRelatorio(string codLeilao, IFormFile file);
        Task<bool> AddLeilaoWishList(Leilao leilao, string username);

        Task<List<WishList>> GetLeilaoWishList(string username);
        Task<bool> RemoveLeilao(string codLeilao);
    }
}
