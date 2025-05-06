using BirdBoxFull.Server.Services.ServicoProduto;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace BirdBoxFull.Server.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class EncomendasController : ControllerBase
    {
        public IServicoEncomenda _servicoEncomenda;
        public EncomendasController(IServicoEncomenda servicoEncomenda)
        {
            _servicoEncomenda = servicoEncomenda;
        }

        [HttpGet("user/{Username}")]
        public async Task<ActionResult<List<Leilao>>> GetLeilaobyUser(string Username)
        {

            return Ok(await _servicoEncomenda.GetEncomendasByUser(Username));
        }

    }
}
