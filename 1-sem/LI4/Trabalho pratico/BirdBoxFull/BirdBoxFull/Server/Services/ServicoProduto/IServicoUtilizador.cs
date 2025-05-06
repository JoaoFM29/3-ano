using BirdBoxFull.Shared;

namespace BirdBoxFull.Server.Services.ServicoProduto
{
    public interface IServicoUtilizador
    {
        Task<Utilizador> GetUtilizador(string Username, string Password);

        Task AddUtilizador(Utilizador newUtilizador);

        Task<bool> AlteraUtilizador(Utilizador updatedUser);
        Task<Utilizador> GetUtilizadorAux(string utilizadorUsername);
        Task<List<Utilizador>> GetUtilizadores();
    }
}
