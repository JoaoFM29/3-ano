using BirdBoxFull.Shared;

namespace BirdBoxFull.Client.Services.ServicoProduto
{
    public interface IServicoLicitacao
    {
        Task<Licitacao> ConsultarLicitacao(String Username,String codLeilao );

        Task AddLicitacao(Licitacao newLiciticao);

        Task ApagarLicitacao(string codLicitacao);

        Task<List<Licitacao>> ConsultarLicitacaoList(String Username);

        Task<List<Licitacao>> ConsultarLicitacaoListAll();

        Task<string> Checkout(Licitacao licitacao);
    }
}
