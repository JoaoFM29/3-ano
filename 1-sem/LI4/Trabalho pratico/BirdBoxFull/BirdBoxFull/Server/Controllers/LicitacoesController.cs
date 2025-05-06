// LicitacoesController.cs
using BirdBoxFull.Server.Services.ServicoProduto;
using BirdBoxFull.Shared;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Threading.Tasks;

namespace BirdBoxFull.Server.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class LicitacoesController : ControllerBase
    {
        private readonly IServicoLicitacao _licitacaoService;
        private readonly IServicoProduto   _produtoService;
        private readonly IPagamentos _pagamentosService;
        private readonly IServicoUtilizador _userService;

        public LicitacoesController(IServicoLicitacao licitacaoService, IServicoProduto produtoService, IPagamentos pagamentos, IServicoUtilizador servicoUtilizador )
        {
            _licitacaoService = licitacaoService;
            _produtoService = produtoService;
            _pagamentosService = pagamentos;
            _userService = servicoUtilizador;
        }

        [HttpPost]
        public async Task<ActionResult> AddLicitacao(Licitacao newLicitacao)
        {
            Console.WriteLine("Tou aqui CONTROLLER FORA");
            try
            {
                Console.WriteLine("Tou aqui CONTROLLER");
                await _licitacaoService.AddLicitacao(newLicitacao);
                return Ok("Licitacao added successfully");
            }
            catch (Exception ex)
            {
                return StatusCode(StatusCodes.Status500InternalServerError, $"Error: {ex.Message}");
            }
        }

        [HttpGet("{username}/{codLeilao}")]
        public async Task<ActionResult<Licitacao>> ConsultarLicitacao(string username, string codLeilao)
        {

        
            try
            {
                var licitacao = await _licitacaoService.ConsultarLicitacao(username, codLeilao);
                if (licitacao != null)
                {
                    return Ok(licitacao);
                }
                else
                {
                    return NotFound("Licitacao not found");
                }
            }
            catch (Exception ex)
            {
                return StatusCode(StatusCodes.Status500InternalServerError, $"Error: {ex.Message}");
            }
        }

		[HttpGet("list/{username}")]
		public async Task<ActionResult<List<Licitacao>>> ConsultarLicitacaoList(string username)
		{
			try
			{
				var licitacoes = await _licitacaoService.ConsultarLicitacaoList(username);
				return Ok(licitacoes);
			}
			catch (Exception ex)
			{
				return StatusCode(StatusCodes.Status500InternalServerError, $"Error: {ex.Message}");
			}
		}
        [HttpGet("listall")]
        public async Task<ActionResult<List<Licitacao>>> ConsultarLicitacaoListAll()
        {
            try
            {
                var licitacoes = await _licitacaoService.ConsultarLicitacaoAll();
                return Ok(licitacoes);
            }
            catch (Exception ex)
            {
                return StatusCode(StatusCodes.Status500InternalServerError, $"Error: {ex.Message}");
            }
        }

        [HttpDelete("{codLicitacao}")]
        public async Task<ActionResult> ApagarLicitacao(string codLicitacao)
        {
            try
            {
                await _licitacaoService.ApagarLicitacao(codLicitacao);
                return Ok("Licitacao deleted successfully");
            }
            catch (Exception ex)
            {
                return StatusCode(StatusCodes.Status500InternalServerError, $"Error: {ex.Message}");
            }
        }

        [HttpPost("pagamento")]
        public async Task<ActionResult> AddCheckout([FromBody] Licitacao licitacao)
        {
            Licitacao l = await _licitacaoService.ConsultarLicitacao(licitacao.UtilizadorUsername, licitacao.LeilaoCodLeilao);
            Console.WriteLine("Licitacao deu");
            Leilao lei = await _produtoService.GetLeilao(l.LeilaoCodLeilao);
            Console.WriteLine("Leilao deu");
            Utilizador comprador = await _userService.GetUtilizadorAux(l.UtilizadorUsername);
            Console.WriteLine("Comprador deu");
            l.Leilao = lei;
            l.Utilizador = comprador;
            Utilizador Vendedor = await _userService.GetUtilizadorAux(lei.UtilizadorUsername);
            lei.Utilizador = Vendedor;
            var resp = _pagamentosService.Checkout(lei, l);

            return Ok(resp);
            
        }
    }
}
