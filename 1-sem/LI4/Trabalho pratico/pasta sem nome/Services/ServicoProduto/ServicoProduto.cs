using BirdBoxFull.Shared;
using Microsoft.AspNetCore.Http;
using System.Net.Http;
using System.Net.Http.Json;

namespace BirdBoxFull.Client.Services.ServicoProduto
{
	public class ServicoProduto : IServicoProduto
	{
        private readonly HttpClient _http;

        public List<Leilao> Leiloes { get; set; } = new List<Leilao>();

        public ServicoProduto(HttpClient httpClient)
        {
            this._http = httpClient;
        }

        public async Task loadLeiloes()
		{

            Leiloes = await _http.GetFromJsonAsync<List<Leilao>>("api/Leiloes");
            
		
		}

        public async Task<Leilao> loadLeilao(string cod)
        {
            return await _http.GetFromJsonAsync<Leilao>($"api/Leiloes/{cod}");
      
        }

        public async Task UploadImages(List<LeilaoImage> images)
        {
            var response = await _http.PostAsJsonAsync("api/Leiloes/upload/image", images);

            if (!response.IsSuccessStatusCode)
            {
                // Handle the error as needed
                // Example: throw new ApplicationException("Image upload failed");
            }
        }

        public async Task AddLeilao(Leilao novoLeilao)
        {
           
            var response = await _http.PostAsJsonAsync("api/Leiloes/regista", novoLeilao);

            if (!response.IsSuccessStatusCode)
            {
                // Handle the error as needed
                // Example: throw new ApplicationException("Image upload failed");
            }
        }
		public async Task<List<Leilao>> GetLeilaoByUser(string Username)
        {

			return await _http.GetFromJsonAsync<List<Leilao>>($"api/Leiloes/user/{Username}");
		}

        public async Task UpdateLeilaoRelatorio(string codLeilao, string fileName, byte[] data)
        {
            // Create FormData and append the file data
            MultipartFormDataContent formData = new MultipartFormDataContent();
            formData.Add(new ByteArrayContent(data), "file", fileName);

            // Send the file data to the server for storage
            var response = await _http.PostAsync($"/api/Leiloes/upload/relatorio/{codLeilao}", formData);
            if (response.IsSuccessStatusCode)
            {
                // Handle success if needed
            }
            else
            {
                // Handle error
                // You may want to display an error message to the user
            }
        }

        public async Task<bool> AddLeilaoWishList(string Leilao, string username)
        {
            Console.WriteLine(Leilao);

            // Send Leilao as JSON in the request body
            var response = await _http.PostAsJsonAsync($"api/Leiloes/wish/{username}", Leilao);
            
            if (!response.IsSuccessStatusCode)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        public async Task<List<WishList>> GetLeilaoWishList(string username)
        {
            return await _http.GetFromJsonAsync<List<WishList>>($"api/Leiloes/wishlistuser/{username}");
        }

        public async Task RemoveLeilao(string codLeilao)
        {
            try
            {
                Console.WriteLine($"{codLeilao}");
                var response = await _http.DeleteAsync($"api/Leiloes/adminremove/{codLeilao}");

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
    }
}
