using System;
using System.Drawing;
using BirdBoxFull.Shared;
using Stripe;
using Stripe.Checkout;

namespace BirdBoxFull.Server.Services.ServicoProduto
{
    public class Pagamentos : IPagamentos
    {
        private readonly string chavePrivada = "sk_test_51OYrugGgqewYMNNJoelzijRk1r6Tosid2HJe9uxUUcxKTgPHcsQ9gUPaBFCKw2BSI5fg5Z3yz3YnIHYxChYQcQoc00HfOGjnh0";
        private readonly string chavePublica = "pk";
        public Pagamentos()
        {
            try
            {
                StripeConfiguration.ApiKey = chavePrivada;

            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }

        }
        public string CreateCustomerStripeAccount(Utilizador utilizador)
        {
            var options = new CustomerCreateOptions
            {
                Name = utilizador.Nome,
                Email = utilizador.email,
                Address = new AddressOptions
                {
                    Line1 = utilizador.rua,
                    PostalCode = utilizador.codigoPostal,
                    City = utilizador.localidade,
                    Country = "PT",
                },
                PaymentMethod = "pm_card_visa",
                InvoiceSettings = new CustomerInvoiceSettingsOptions
                {
                    DefaultPaymentMethod = "pm_card_visa",
                },

            };
            var service = new CustomerService();
            var customer = service.Create(options);
            return customer.Id;

        }

        public string CreateCustomerAccount(Utilizador utilizador)
        {
            var options = new AccountCreateOptions
            {
                Type = "custom",
                Country = "PT",
                Email = utilizador.email,
                Capabilities = new AccountCapabilitiesOptions
                {
                    CardPayments = new AccountCapabilitiesCardPaymentsOptions
                    {
                        Requested = true,
                    },
                    Transfers = new AccountCapabilitiesTransfersOptions
                    {
                        Requested = true,
                    },
                },
                BusinessType = "individual",
                Individual = new AccountIndividualOptions
                {
                    FirstName = utilizador.Nome,
                    LastName = utilizador.Nome,
                    Email = utilizador.email,
                    Address = new AddressOptions
                    {
                        Line1 = "address_full_match",
                        PostalCode = "4590-182",
                        City = utilizador.localidade,
                        Country = "PT",
                    },
                    Dob = new DobOptions
                    {
                        Day = 1,
                        Month = 1,
                        Year = 1990,
                    },
                    IdNumber = "000000000",
                    Phone = "000-000-0000",
                },
                BusinessProfile = new AccountBusinessProfileOptions
                {
                    Mcc = "5734",
                    Url = "https://accessible.stripe.com/",
                },
                ExternalAccount = new AccountBankAccountOptions
                {
                    AccountNumber = "PT50000201231234567890154",
                    Country = "PT",
                    Currency = "eur",
                    AccountHolderName = utilizador.Nome,
                    AccountHolderType = "individual",
                },
                TosAcceptance = new AccountTosAcceptanceOptions
                {
                    Date = DateTime.Now,
                    Ip = "8.8.8.8"
                }
               
            };
            try
            {
                var service = new AccountService();
                var account = service.Create(options);
                return account.Id;
            }
            catch (StripeException stripeException)
            {
                // Log or print the exception details for troubleshooting
                Console.WriteLine($"Stripe Exception: {stripeException.Message}");

                Console.WriteLine($"Error Type: {stripeException.StripeError.Type}");

                // Handle the exception or rethrow if needed
                throw;
            }
            catch (Exception ex)
            {
                // Log or print the general exception details for troubleshooting
                Console.WriteLine($"General Exception: {ex.Message}");

                // Handle the exception or rethrow if needed
                throw;
            }

        }

        public bool UpdateCustomerStripeAccount(string id, Utilizador updateUser)
        {
            var options = new CustomerUpdateOptions
            {
                Name = updateUser.Nome,
                Email = updateUser.email,
                Address = new AddressOptions
                {
                    Line1 = updateUser.rua,
                    PostalCode = updateUser.codigoPostal,
                    City = updateUser.localidade,
                    Country = "PT",
                }

            };
            var service = new CustomerService();
            var customer = service.Update(id, options);
            return true;
        }

        //create a SessionLineItemOptions with name, price and image
        
        public SessionLineItemOptions CreateSessionLineItem(Leilao leilao, Licitacao licitacao)
        {
            var lineItem = new SessionLineItemOptions
            {
                PriceData = new SessionLineItemPriceDataOptions
                {
                    UnitAmount = Convert.ToInt64(licitacao.valor * 100),
                    Currency = "eur",
                    ProductData = new SessionLineItemPriceDataProductDataOptions
                    {
                        Name = leilao.Name,
                    },
                   
                },
                Quantity = 1,
            };
            return lineItem;
        }
        //create a checkout session with  customer id and products list

        /*
        public Stripe.Checkout.Session CreateCheckoutSession(Leilao leilao, Licitacao licitacao) // Garantir que a Licitacao tem o Utilizador direito e que o Leilao tá deireito também
        {
            Console.WriteLine("Segundo Aqui");

            var lineItems = new List<SessionLineItemOptions>();
            lineItems.Add(CreateSessionLineItem(leilao, licitacao));

            var options = new SessionCreateOptions
            {
                Customer = licitacao.Utilizador.StripeId,
                PaymentMethodTypes = new List<string>
            {
                "card",
            },
                Metadata = new Dictionary<string, string> { { "codLicitacao", licitacao.codLicitacao } },
                ExpiresAt =DateTime.Now.AddDays(0.8),
                LineItems = lineItems,
                Mode = "payment",
                SuccessUrl = "https://localhost:7062",
                CancelUrl = "https://localhost:7062"
                
            };
            var service = new SessionService();
            var session = service.Create(options);

            return session;
        }
        //exprire a checkout session
        public bool ExpireCheckoutSession(string id)
        {
            var service = new SessionService();
            service.Expire(id);
            return true;
        }
        */
        public async Task<string> Checkout(Leilao leilao,Licitacao licitacao)
        {
            Console.WriteLine("Primeor Aqui");
            return CreateCheckoutSession(leilao, licitacao).Url;
        }

        
   
        //create shipping options
        public List<SessionShippingOptionOptions> sessionShippingOptionOptions()
        {
            var shippingOptions = new List<SessionShippingOptionOptions>
     {
         new SessionShippingOptionOptions
         {
         ShippingRateData = new SessionShippingOptionShippingRateDataOptions
         {
             Type = "fixed_amount",
             FixedAmount = new SessionShippingOptionShippingRateDataFixedAmountOptions
             {
                 Amount = 0,
                 Currency = "eur",
             },
             DisplayName = "Free shipping",
             DeliveryEstimate = new SessionShippingOptionShippingRateDataDeliveryEstimateOptions
             {
                 Minimum = new SessionShippingOptionShippingRateDataDeliveryEstimateMinimumOptions
                 {
                     Unit = "business_day",
                     Value = 5,
                 },
                 Maximum = new SessionShippingOptionShippingRateDataDeliveryEstimateMaximumOptions
                 {
                     Unit = "business_day",
                     Value = 7,
                 },
             },
         },
         },
         new SessionShippingOptionOptions
         {
             ShippingRateData = new SessionShippingOptionShippingRateDataOptions
             {
                 Type = "fixed_amount",
                 FixedAmount = new SessionShippingOptionShippingRateDataFixedAmountOptions
                 {
                     Amount = 1500,
                     Currency = "eur",
                 },
                 DisplayName = "Next day air",
                 DeliveryEstimate = new SessionShippingOptionShippingRateDataDeliveryEstimateOptions
                 {
                     Minimum = new SessionShippingOptionShippingRateDataDeliveryEstimateMinimumOptions
                     {
                         Unit = "business_day",
                         Value = 1,
                     },
                     Maximum = new SessionShippingOptionShippingRateDataDeliveryEstimateMaximumOptions
                     {
                         Unit = "business_day",
                         Value = 1,
                     },
                 },
             },
         },
     };
            return shippingOptions;
        }
        //create a checkout session with  customer id and products list
        public Session CreateCheckoutSession(Leilao leilao, Licitacao licitacao)
        {


            var lineItems = new List<SessionLineItemOptions>();
            lineItems.Add(CreateSessionLineItem(leilao, licitacao));

            var options = new SessionCreateOptions
            {
                Customer = licitacao.Utilizador.StripeId,
                PaymentMethodTypes = new List<string>
         {
             "card",
         },
                ShippingAddressCollection = new SessionShippingAddressCollectionOptions
                {
                    AllowedCountries = new List<string> { "US", "CA", "PT" },
                },
                ShippingOptions = sessionShippingOptionOptions(),
                Metadata = new Dictionary<string, string> { { "codLicitacao", licitacao.codLicitacao } },
                ExpiresAt = DateTime.Now.AddDays(0.8),
                LineItems = lineItems,
                Mode = "payment",
                PaymentIntentData = new SessionPaymentIntentDataOptions
                {
                    ApplicationFeeAmount = Convert.ToInt64(licitacao.valor * 100 * 0.1),
                    TransferData = new SessionPaymentIntentDataTransferDataOptions
                    {
                        Destination = leilao.Utilizador.AccountStripeId,
                    },
                },
                SuccessUrl = "https://localhost:7062",
                CancelUrl = "https://localhost:7062",

            };
            var service = new SessionService();
            var session = service.Create(options);
            return session;
        }


    }



}
