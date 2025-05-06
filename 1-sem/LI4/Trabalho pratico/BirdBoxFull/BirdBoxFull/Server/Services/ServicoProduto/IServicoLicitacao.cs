using BirdBoxFull.Shared;

namespace BirdBoxFull.Server.Services.ServicoProduto
{
    public interface IServicoLicitacao
    {
        Task<Licitacao> ConsultarLicitacao(String Username, String codLeilao);

        Task AddLicitacao(Licitacao newLiciticao);

        Task ApagarLicitacao(string codLicitacao);
		Task<List<Licitacao>> ConsultarLicitacaoList(String Username);

        Task<List<Licitacao>> ConsultarLicitacaoAll();

        Task AlterarEstado(string codLicitacao, string novoEstado);

        Task<List<Licitacao>> ConsultarLicitacaoListLei(string codLeilao);

        Task AlterarIsWining(string codLicitacao, bool isW);
        Task <Licitacao> GetLicitacao(string bidId);
    }
}
