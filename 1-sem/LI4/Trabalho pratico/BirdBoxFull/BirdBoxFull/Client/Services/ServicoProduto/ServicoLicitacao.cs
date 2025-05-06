// ServicoLicitacao.cs in the Client project
using System.Net;
using System.Net.Http;
using System.Net.Http.Json;
using System.Threading.Tasks;
using BirdBoxFull.Shared;

namespace BirdBoxFull.Client.Services.ServicoProduto
{
    public class ServicoLicitacao : IServicoLicitacao
    {
        private readonly HttpClient _http;

        public ServicoLicitacao(HttpClient httpClient)
        {
            this._http = httpClient;
        }

        public async Task AddLicitacao(Licitacao newLicitacao)
        {
            // Adjust the API endpoint based on your server setup
            newLicitacao.Leilao.WishLists = new List<WishList>();
            newLicitacao.Leilao.Encomenda = null;
            newLicitacao.Leilao.Licitacoes = new List<Licitacao>();
            newLicitacao.Leilao.Utilizador = new Utilizador();
            var response = await _http.PostAsJsonAsync("api/Licitacoes", newLicitacao);

            if (!response.IsSuccessStatusCode)
            {
                Console.WriteLine("MERDA");
            }
        }

        

        public async Task<Licitacao> ConsultarLicitacao(string username, string codLeilao)
        {
            try
            {
                // Adjust the API endpoint based on your server setup
                var response = await _http.GetFromJsonAsync<Licitacao>($"api/Licitacoes/{username}/{codLeilao}");

                return response;
            }
            catch (HttpRequestException ex)
            {
                return null;

               
            }
        }

		public async Task<List<Licitacao>> ConsultarLicitacaoList(string username)
		{
			try
			{
				// Adjust the API endpoint based on your server setup
				var response = await _http.GetFromJsonAsync<List<Licitacao>>($"api/Licitacoes/list/{username}");

				return response ?? new List<Licitacao>();
			}
			catch (HttpRequestException)
			{
				// Handle the exception, log, or return an empty list as needed
				return new List<Licitacao>();
			}
		}

        public async Task ApagarLicitacao(string codLicitacao)
        {
            try
            {
                var response = await _http.DeleteAsync($"api/Licitacoes/{codLicitacao}");

                if (!response.IsSuccessStatusCode)
                {
                    Console.WriteLine("Error deleting Licitacao");
                }
            }
            catch (HttpRequestException)
            {
                Console.WriteLine("Error deleting Licitacao");
            }
        }

        public async Task<string> Checkout(Licitacao licitacao)
        {
            licitacao.Leilao.Licitacoes = new List<Licitacao>();
            licitacao.Leilao.WishLists = new List<WishList>();
            licitacao.Leilao.Utilizador = new Utilizador();
            licitacao.Utilizador = new Utilizador();
            var response = await _http.PostAsJsonAsync("api/Licitacoes/pagamento", licitacao);

            var url = await response.Content.ReadAsStringAsync();

            return url; 
        }

        public async Task<List<Licitacao>> ConsultarLicitacaoListAll()
        {
            try
            {
                // Adjust the API endpoint based on your server setup
                var response = await _http.GetFromJsonAsync<List<Licitacao>>($"api/Licitacoes/listall");

                return response ?? new List<Licitacao>();
            }
            catch (HttpRequestException)
            {
                // Handle the exception, log, or return an empty list as needed
                return new List<Licitacao>();
            }
        }
    }
}
