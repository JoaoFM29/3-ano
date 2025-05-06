using BirdBoxFull.Shared;
using Stripe.BillingPortal;

namespace BirdBoxFull.Server.Services.ServicoProduto
{
    public interface IPagamentos
    {

        string CreateCustomerStripeAccount(Utilizador newUtilizador);
        bool UpdateCustomerStripeAccount(String stripId, Utilizador updatedUser);
        Task<string> Checkout(Leilao leilao,Licitacao licitacao);

        string CreateCustomerAccount(Utilizador utilizador);

    }
}