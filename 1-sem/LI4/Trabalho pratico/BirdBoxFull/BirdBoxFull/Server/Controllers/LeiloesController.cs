using BirdBoxFull.Server.Services.ServicoProduto;
using BirdBoxFull.Shared;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace BirdBoxFull.Server.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class LeiloesController : ControllerBase
    {
        public IServicoProduto _productService;
        public LeiloesController(IServicoProduto productService)
        {
            _productService = productService;
        }

        [HttpGet]
        public async Task<ActionResult<List<Leilao>>> GetLeiloes()
        {
            return Ok(await _productService.GetAllLeiloes());
        }

        [HttpGet("wishlistuser/{Username}")]
        public async Task<ActionResult<List<WishList>>> GetWishUser(string Username)
        {
            return Ok(await _productService.GetLeilaoWishList(Username));
        }

        [HttpGet("{codLeilao}")]
        public async Task<ActionResult<Leilao>> GetLeilao(string codLeilao)
        {
            return Ok(await _productService.GetLeilao(codLeilao));
        }

        [HttpGet("user/{Username}")]
        public async Task<ActionResult<List<Leilao>>> GetLeilaobyUser(string Username)
        {

            return Ok(await _productService.GetLeilaoByUser(Username));
        }

        [HttpPost("upload/image")] // Updated route
        public async Task<ActionResult> UploadImages([FromBody] List<LeilaoImage> images)
        {
            try
            {
                // Process the request and save the images to the database using the ProductService
                await _productService.UploadImages(images);

                return Ok("Images uploaded successfully");
            }
            catch (Exception ex)
            {
                return StatusCode(StatusCodes.Status500InternalServerError, $"Error: {ex.Message}");
            }
        }

        [HttpPost("regista")] // New action method to add a new auction
        public async Task<ActionResult> AddLeilao([FromBody] Leilao novoLeilao)
        {

            try
            {
                // Process the request and add the new auction to the database using the ProductService
                await _productService.AddLeilao(novoLeilao);


                return Ok("Auction added successfully");
            }
            catch (Exception ex)
            {

                return StatusCode(StatusCodes.Status500InternalServerError, $"Error: {ex.Message}");
            }
        }

        [HttpPost("upload/relatorio/{codLeilao}")]
        public async Task<IActionResult> UploadRelatorio(string codLeilao, [FromForm] FileUploadDto fileUploadDto)
        {

            if (fileUploadDto?.File != null && fileUploadDto.File.Length > 0)
            {
                Console.WriteLine("Dentro do IF");
                await _productService.UpdateLeilaoRelatorio(codLeilao, fileUploadDto.File);
                // Return a success response if needed
                return Ok("File uploaded successfully");
            }

            return BadRequest("Invalid file.");
        }

        [HttpPost("wish/{username}")]
        public async Task<IActionResult> AddLeilaoWishList(string username, [FromBody] string Leilao)
        {
            Console.WriteLine("CHEGOU AQUI MEU");

            // Now Leilao is expected in the request body as JSON
            Leilao lei = await _productService.GetLeilao(Leilao);
            bool b = await _productService.AddLeilaoWishList(lei, username);

            if (b)
            {
                return Ok("Alteracao realizada");
            }
            else
            {
                return BadRequest("Dono do leilao nao pode adicionar como desejo");
            }
        }

        [HttpDelete("adminremove/{codLeilao}")]
        public async Task<IActionResult> removeLeilao(string codLeilao)
        {
          


            bool b = await _productService.RemoveLeilao(codLeilao);

            if (b)
            {
                return Ok("Leilao Removido");
            }
            else
            {
                return BadRequest("ERRO");
            }

            


        }
    }
}


