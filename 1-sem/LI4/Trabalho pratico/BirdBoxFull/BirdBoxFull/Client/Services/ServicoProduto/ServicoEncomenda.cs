using BirdBoxFull.Client.Services.ServicoProduto;
using BirdBoxFull.Shared;
using System.Net.Http.Json;
using static System.Net.WebRequestMethods;

namespace BirdBoxFull.Client.Services.ServicoProduto
{
    public class ServicoEncomenda : IServicoEncomenda
    {
        private readonly HttpClient _http;
        public ServicoEncomenda(HttpClient httpClient)
        {
          
            this._http = httpClient;
        
         }
        public Task addEncomenda(Encomenda e)
        {
            throw new NotImplementedException();
        }

        public Task<Encomenda> GetEncomenda(string codEncomenda)
        {
            throw new NotImplementedException();
        }

        public Task<List<Encomenda>> GetEncomendas()
        {
            throw new NotImplementedException();
        }

        public async Task<List<Encomenda>> GetEncomendasByUser(string Username)
        {
            return await _http.GetFromJsonAsync<List<Encomenda>>($"api/Encomendas/user/{Username}");
        }
    }
}
