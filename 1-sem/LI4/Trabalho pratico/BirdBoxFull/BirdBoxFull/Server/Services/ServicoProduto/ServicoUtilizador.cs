using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using BirdBoxFull.Shared;
using BirdBoxFull.Server.Data;

namespace BirdBoxFull.Server.Services.ServicoProduto
{
    public class ServicoUtilizador : IServicoUtilizador
    {
        private readonly DataContext _context;
        private readonly IPagamentos _pagamentos;

        public ServicoUtilizador(DataContext dataContext)
        {
            _context = dataContext;
            _pagamentos = new Pagamentos();
        }

        public async Task<Utilizador> GetUtilizador(string Username, string Password)
        {

            var user = await _context.Utilizadores
                .FirstOrDefaultAsync(u => u.Username.Equals(Username));

            if (user != null && VerifyPassword(user, Password))
            {
                return user;
            }
            return null;
        }
        private bool VerifyPassword(Utilizador user, string password)
        {
            return user.Password.Equals(password);
        }

        public async Task AddUtilizador(Utilizador newUtilizador)
        {
            newUtilizador.StripeId = _pagamentos.CreateCustomerStripeAccount(newUtilizador);
            newUtilizador.AccountStripeId = _pagamentos.CreateCustomerAccount(newUtilizador);
            var user = await _context.Utilizadores
                .FirstOrDefaultAsync(u => u.Username.Equals(newUtilizador.Username));


            if (user != null)
            {
                throw new InvalidOperationException("Username is already taken");
            }

            if (newUtilizador == null)
            {
                throw new ArgumentNullException(nameof(newUtilizador));
            }

            _context.Utilizadores.Add(newUtilizador);
            await _context.SaveChangesAsync();
        }

        public async Task<bool> AlteraUtilizador(Utilizador updatedUser)
        {
            try
            {
                var existingUser = await _context.Utilizadores
                    .FirstOrDefaultAsync(u => u.Username.Equals(updatedUser.Username));

                if (existingUser != null)
                {
                    // Update user properties
                    existingUser.Nome = updatedUser.Nome;
                    existingUser.email = updatedUser.email;
                    existingUser.numeroTelemovel = updatedUser.numeroTelemovel;
                    existingUser.localidade = updatedUser.localidade;
                    existingUser.rua = updatedUser.rua;
                    existingUser.numeroPorta = updatedUser.numeroPorta;
                    existingUser.codigoPostal = updatedUser.codigoPostal;
                    // Update other properties as needed
                    _pagamentos.UpdateCustomerStripeAccount(existingUser.StripeId, updatedUser);
                    await _context.SaveChangesAsync();
                    return true;
                }

                // User not found
                return false;
            }
            catch (Exception)
            {
                // Handle exceptions if needed
                return false;
            }
        }

        public async Task<Utilizador> GetUtilizadorAux(string utilizadorUsername)
        {
            var user = await _context.Utilizadores
                .FirstOrDefaultAsync(u => u.Username.Equals(utilizadorUsername));
                return user;
          
        }

        public async Task<List<Utilizador>> GetUtilizadores()
        {
            return await _context.Utilizadores.ToListAsync();
        }
    }
}