// ServicoLicitacao.cs
using BirdBoxFull.Server.Data;
using BirdBoxFull.Shared;
using Microsoft.EntityFrameworkCore;
using System;
using System.Linq;
using System.Threading.Tasks;

namespace BirdBoxFull.Server.Services.ServicoProduto
{
    public class ServicoLicitacao : IServicoLicitacao
    {
        private readonly DataContext _context;

        private readonly IPagamentos _pagamentos;

        public ServicoLicitacao(DataContext context, IPagamentos pagamentos)
        {
            _context = context;
            _pagamentos = pagamentos;
        }

        public async Task AddLicitacao(Licitacao newLicitacao)
        {

           

            // Assuming novoLeilao.Utilizador is the associated Utilizador
            var existingUtilizador = await _context.Utilizadores.FindAsync(newLicitacao.UtilizadorUsername);
            var existingLeilao = await _context.Leiloes.FindAsync(newLicitacao.LeilaoCodLeilao);

            // Attach or load the Utilizador
            if (existingUtilizador != null)
            {
                _context.Entry(existingUtilizador).State = EntityState.Unchanged;
                newLicitacao.Utilizador = existingUtilizador;
            }

            if (existingLeilao != null)
            {
                _context.Entry(existingLeilao).State = EntityState.Unchanged;
                newLicitacao.Leilao = existingLeilao;
            }
            _context.Licitacoes.Add(newLicitacao);
            await _context.SaveChangesAsync();
        }

        public async Task<Licitacao> ConsultarLicitacao(string username, string codLeilao)
        {
            return await _context.Licitacoes
                .Where(l => l.UtilizadorUsername.Equals(username) && l.LeilaoCodLeilao.Equals(codLeilao))
                .FirstOrDefaultAsync();
        }

		public async Task<List<Licitacao>> ConsultarLicitacaoList(string Username)
		{
			return await _context.Licitacoes
				.Where(l => l.UtilizadorUsername.Equals(Username))
				.ToListAsync();
		}

        public async Task<List<Licitacao>> ConsultarLicitacaoListLei(string codLeilao)
        {
            return await _context.Licitacoes
                .Where(l => l.LeilaoCodLeilao.Equals(codLeilao))
                .ToListAsync();
        }

        public async Task ApagarLicitacao(string codLicitacao)
        {
            var licitacaoToDelete = await _context.Licitacoes.FindAsync(codLicitacao);

            if (licitacaoToDelete != null)
            {
                _context.Licitacoes.Remove(licitacaoToDelete);
                await _context.SaveChangesAsync();
            }
            else
            {
                throw new ArgumentException("Licitacao not found");
            }
        }

        public async Task AlterarEstado(string codLicitacao, string novoEstado)
        {
            try
            {
                // Retrieve the Licitacao from the database based on codLicitacao
                Licitacao licitacao = await _context.Licitacoes.FindAsync(codLicitacao);

                if (licitacao != null)
                {
                    // Update the estado property
                    licitacao.Estado = novoEstado;

                    // Save the changes to the database
                    await _context.SaveChangesAsync();
                }
                else
                {
                    // Handle the case where the Licitacao with the provided codLicitacao is not found
                    throw new KeyNotFoundException($"Licitacao with codLicitacao {codLicitacao} not found.");
                }
            }
            catch (Exception ex)
            {
                // Handle other exceptions if needed
                throw new Exception($"Error updating Licitacao estado: {ex.Message}", ex);
            }
        }
        public async Task AlterarIsWining(string codLicitacao, bool isW)
        {
            try
            {
                // Retrieve the Licitacao from the database based on codLicitacao
                Licitacao licitacao = await _context.Licitacoes.FindAsync(codLicitacao);

                if (licitacao != null)
                {
                    // Update the estado property
                    licitacao.isWinner = isW;

                    // Save the changes to the database
                    await _context.SaveChangesAsync();
                }
                else
                {
                    // Handle the case where the Licitacao with the provided codLicitacao is not found
                    throw new KeyNotFoundException($"Licitacao with codLicitacao {codLicitacao} not found.");
                }
            }
            catch (Exception ex)
            {
                // Handle other exceptions if needed
                throw new Exception($"Error updating Licitacao estado: {ex.Message}", ex);
            }
        }

        public async Task<Licitacao> GetLicitacao(string bidId)
        {
            return await _context.Licitacoes
                .Where(l => l.codLicitacao.Equals(bidId)).FirstOrDefaultAsync();

        }

        public async Task<List<Licitacao>> ConsultarLicitacaoAll()
        {
            return await _context.Licitacoes.ToListAsync();
        }
    }
}
