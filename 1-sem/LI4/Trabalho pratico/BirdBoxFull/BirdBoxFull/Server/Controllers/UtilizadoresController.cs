using BirdBoxFull.Server.Services.ServicoProduto;
using BirdBoxFull.Shared;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.IdentityModel.Tokens;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Security.Cryptography;
using static System.Net.WebRequestMethods;
using System.Text.Json;
using System.Text;
using Stripe;

namespace BirdBoxFull.Server.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class UtilizadoresController : ControllerBase
    {
        public IServicoUtilizador _utilizadorService;

        public UtilizadoresController(IServicoUtilizador utilizadorService)
        {
            _utilizadorService = utilizadorService;
        }

        [HttpGet("login/{Username}/{Password}")]
        public async Task<ActionResult<Utilizador>> GetUtilizador(string Username, string Password)
        {
            Console.WriteLine(Username + " " + Password);
            
            Utilizador u = await _utilizadorService.GetUtilizador(Username, Password);

            

            if (u == null)
            {
                Console.WriteLine("Nulo");
                return BadRequest();
            }
            else
            {
                return Ok(u);
            }
        }

        [HttpGet("all/users/admin")]
        public async Task<ActionResult<List<Utilizador>>> GetUtilizadores()
        {
            Console.WriteLine("HERE!");
            return Ok(await _utilizadorService.GetUtilizadores());
        }

        [HttpGet("stripe/{id}")]
        public async Task<ActionResult<string>> GetUtilizadorStripe(string id)
        {
            try
            {
                // Create an Express account link
                var options = new AccountLinkCreateOptions
                {
                    Account = id,
                    RefreshUrl = "https://localhost:7062",
                    ReturnUrl = "https://localhost:7062",
                    Type = "account_onboarding",
                };

                var service = new AccountLinkService();
                var accountLink = await service.CreateAsync(options);

                return Ok(accountLink.Url);
            }
            catch (Exception ex)
            {
                // Log or handle the exception
                Console.WriteLine($"Exception: {ex.Message}");
                return BadRequest("Error occurred");
            }
        }

        /*
        [HttpPut("{username}")]
        public async Task<IActionResult> UpdateUtilizador(string username, [FromBody] Utilizador updatedUtilizador)
        {
            
            if (updatedUtilizador == null || !ModelState.IsValid)
            {
                return BadRequest("Invalid data");
            }

            var existingUtilizador = await _utilizadorService.GetUtilizadorByUsername(username);

            if (existingUtilizador == null)
            {
                return NotFound();
            }

            // Update properties of existingUtilizador with updatedUtilizador
            existingUtilizador.Password = updatedUtilizador.Password;
            existingUtilizador.dataNascimento = updatedUtilizador.dataNascimento;
            existingUtilizador.metodoPagamento = updatedUtilizador.metodoPagamento;
            // ... update other properties ...

            // Save changes to the repository (this will depend on your data access layer)
            await _utilizadorService.UpdateUtilizador(existingUtilizador);

            return NoContent(); // 204 No Content indicates a successful update with no response body
            
    }
    */
        [HttpPost("regista")]
        public async Task<IActionResult> RegistaUtilizador([FromBody] Utilizador newUtilizador)
        {
            
            if (newUtilizador == null || !ModelState.IsValid)
            {
                return BadRequest("Invalid data");
            }
           

            // Perform necessary validation, and then add the new user to the repository
            try
            {
                await _utilizadorService.AddUtilizador(newUtilizador);
            }catch(Exception ex)
            {
                return BadRequest("Deu erro");
            }

            return CreatedAtAction("RegistaUtilizador", new { username = newUtilizador.Username }, newUtilizador);
        }

        [HttpPut("altera")]
        public async Task<IActionResult> AlteraUtilizador([FromBody] Utilizador updatedUser)
        {
            var success = await _utilizadorService.AlteraUtilizador(updatedUser);

            if (success)
            {
                return Ok();
            }

            return NotFound();
        }
        


    }

}

