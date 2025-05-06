using BirdBoxFull.Shared;
using System.Net.Http;
using System.Net.Http.Json;
using System.Text.Json;
using System.Text;

namespace BirdBoxFull.Client.Services.ServicoProduto
{
    public class ServicoUtilizador : IServicoUtilizador
    {
        public Utilizador Utilizador { get; set;} = new Utilizador();

        private readonly HttpClient _http;

        public ServicoUtilizador(HttpClient httpClient)
        {
            this._http = httpClient;
        }


        public async Task<Utilizador> GetUtilizador(string username, string password)
        {
            var response = await _http.GetAsync($"api/Utilizadores/login/{username}/{password}");

            if (response.IsSuccessStatusCode)
            {
                return await response.Content.ReadFromJsonAsync<Utilizador>();
            }
            else
            {
                
                Console.WriteLine($"Error: {response.StatusCode}");
                return null;
            }
        }

        public async Task<bool> UpdateUtilizador(Utilizador updatedUtilizador)
        {
            // Assuming your API supports updating via HTTP PUT or PATCH
            // Adjust the endpoint and HTTP method accordingly based on your API design

            // Convert Utilizador to JSON
            var jsonContent = new StringContent(
                JsonSerializer.Serialize(updatedUtilizador),
                Encoding.UTF8,
                "application/json"
            );

            // Send HTTP PUT or PATCH request
            var response = await _http.PutAsync($"api/Utilizadores/{updatedUtilizador.Username}", jsonContent);

            if (response.IsSuccessStatusCode)
            {
                // Utilizador updated successfully
                return true;
            }
            else
            {
                Console.WriteLine($"Error: {response.StatusCode}");
                return false;
            }
        }

        public async Task<bool> AddUtilizador(Utilizador newUser)
        {
            try
            {
                Console.WriteLine(newUser.Nome);
                var response = await _http.PostAsJsonAsync("/api/Utilizadores/regista", newUser);

                if (response.IsSuccessStatusCode)
                {
                    // Registration successful
                    return true;
                }
                else
                {
                    // Handle registration failure (e.g., log the error)
                    Console.WriteLine($"ErrorService: {response.StatusCode}");
                    return false;
                }
            }
            catch (Exception ex)
            {
                // Handle unexpected exceptions
                Console.WriteLine($"ExceptionService: {ex.Message}");
                return false;
            }
        }

        public async Task<bool> AlteraUtilizador(Utilizador User)
        {
            try
            {
                var response = await _http.PutAsJsonAsync("/api/Utilizadores/altera", User);

                if (response.IsSuccessStatusCode)
                {
                    // User update successful
                    return true;
                }
                else
                {
                    // Handle update failure (e.g., log the error)
                    Console.WriteLine($"Error: {response.StatusCode}");
                    return false;
                }
            }
            catch (Exception ex)
            {
                // Handle unexpected exceptions
                Console.WriteLine($"Exception: {ex.Message}");
                return false;
            }
        }

        public async Task<string> getStripe(string stripeAccId)
        {
            var response = await _http.GetAsync($"api/Utilizadores/stripe/{stripeAccId}");

            if (response.IsSuccessStatusCode)
            {
                var result = await response.Content.ReadAsStringAsync();
                Console.WriteLine("Success! Result: " + result);
                return result;
            }
            else
            {
                Console.WriteLine($"Error: {response.StatusCode}");
                var errorText = await response.Content.ReadAsStringAsync();
                Console.WriteLine("Error Content: " + errorText);
                return null;
            }
        }

        public async Task<List<Utilizador>> GetUtilizadores()
        {
            try
            {
                var response = await _http.GetFromJsonAsync<List<Utilizador>>("api/Utilizadores/all/users/admin");
                Console.WriteLine("Response received:", response);
                return  response ?? new List<Utilizador>();
               
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error loading utilizadores:", ex.Message);
                return new List<Utilizador>(); 
            }

        }
    }
}
