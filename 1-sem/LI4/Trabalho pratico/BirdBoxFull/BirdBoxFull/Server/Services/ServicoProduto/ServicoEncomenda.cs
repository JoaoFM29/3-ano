using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using BirdBoxFull.Server.Data;
using BirdBoxFull.Shared;

namespace BirdBoxFull.Server.Services.ServicoProduto
{
    public class ServicoEncomenda : IServicoEncomenda
    {
        private readonly DataContext _context;

        public ServicoEncomenda(DataContext context)
        {
            _context = context;
        }

        public async Task addEncomenda(Encomenda e)
        {
            e.Utilizador = await _context.Utilizadores.FirstOrDefaultAsync(p => p.Username.Equals(e.UtilizadorUsername));
            e.Leilao = await _context.Leiloes.FirstOrDefaultAsync(p => p.CodLeilao.Equals(e.LeilaoCodLeilao));
            _context.Encomendas.Add(e);
            await _context.SaveChangesAsync();
        }

        public async Task<Encomenda> GetEncomenda(string codEncomenda)
        {
            return await _context.Encomendas.FirstOrDefaultAsync(p => p.codEncomenda.Equals(codEncomenda));
        }

        public async Task<List<Encomenda>> GetEncomendas()
        {
            return await _context.Encomendas.ToListAsync();
        }

        public async Task<List<Encomenda>> GetEncomendasByUser(string username)
        {
            return await _context.Encomendas
                .Where(e => e.UtilizadorUsername.Equals(username))
                .ToListAsync();
        }
    }
}
