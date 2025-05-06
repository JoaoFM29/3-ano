using BirdBoxFull.Client.Shared;
using BirdBoxFull.Server.Data;
using BirdBoxFull.Shared;
using Microsoft.AspNetCore.Hosting;
using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using System.Reflection.Metadata.Ecma335;
using System.Xml.Linq;

namespace BirdBoxFull.Server.Services.ServicoProduto
{
    public class ServicoProduto : IServicoProduto
    {
        /* public List<Leilao> Leiloes { get; set; } = new List<Leilao>{

                 new Leilao("ide","user1","Ganda Leilao",10,"nope","a decorrer", new List<string> {"https://picsum.photos/200/300", "https://picsum.photos/200/300", "https://picsum.photos/200/300","https://picsum.photos/200/300"},
                     "Produto",
                     10,
                     "Banladesh",
                      true,

                 new DateTime(2024, 1, 15, 5, 10, 20)),

             };*/

        private readonly DataContext _context;

        private readonly IServicoLicitacao _licitacoes;

        private readonly IServicoUtilizador _servicoUtilizador;

        private readonly IEmailSenderService _emailSenderService;

        private readonly IWebHostEnvironment _webHostEnvironment;

        public ServicoProduto(DataContext context, IServicoLicitacao licitacoes, IWebHostEnvironment webHostEnvironment, IServicoUtilizador servicoUtilizador, IEmailSenderService emailSenderService)
        {
            _context = context;
            _licitacoes = licitacoes;
            _webHostEnvironment = webHostEnvironment;
            _servicoUtilizador = servicoUtilizador;
            _emailSenderService = emailSenderService;
        }

        public async Task<List<Leilao>> GetAllLeiloes()
        {

            List<Leilao> l = await _context.Leiloes.ToListAsync();
            foreach (Leilao le in l)
            {

                string codLeilaoToFilter = le.CodLeilao; // Replace with the actual value you're looking for

                List<LeilaoImage> filteredImages = await _context.LeilaoImages
                    .Where(image => image.LeilaoCodLeilao == codLeilaoToFilter)
                    .ToListAsync();

                foreach (var image in filteredImages)
                {
                    le.Images.Add(image.ImageUrl);
                }

            }
            return l;
            // return Leiloes;

        }

        public async Task<Leilao> GetLeilao(string codLeilao)
        {

            Leilao l = await _context.Leiloes.FirstOrDefaultAsync(p => p.CodLeilao.Equals(codLeilao)).ConfigureAwait(false);

            string codLeilaoToFilter = l.CodLeilao; // Replace with the actual value you're looking for

            List<LeilaoImage> filteredImages = await _context.LeilaoImages
                .Where(image => image.LeilaoCodLeilao == codLeilaoToFilter)
                .ToListAsync();
            foreach (var image in filteredImages)
            {
                l.Images.Add(image.ImageUrl);
            }

            return l;
        }

        public async Task<List<Leilao>> GetLeilaoByFiltro(List<string> filtros)
        {
            throw new NotImplementedException();
        }


        public async Task UploadImages(List<LeilaoImage> images)
        {
            foreach (var image in images)
            {
                // Assuming Leilao associated with the LeilaoImage
                var existingLeilao = await _context.Leiloes.FindAsync(image.LeilaoCodLeilao);

                // Attach or load the Leilao
                if (existingLeilao != null)
                {
                    _context.Entry(existingLeilao).State = EntityState.Unchanged;
                    image.Leilao = existingLeilao;
                }

                // You can customize this logic based on your database structure and relationships
                _context.LeilaoImages.Add(image);
            }

            await _context.SaveChangesAsync();
        }

        public async Task AddLeilao(Leilao novoLeilao)
        {


            // Assuming novoLeilao.Utilizador is the associated Utilizador
            var existingUtilizador = await _context.Utilizadores.FindAsync(novoLeilao.Utilizador.Username);

            // Attach or load the Utilizador
            if (existingUtilizador != null)
            {
                _context.Entry(existingUtilizador).State = EntityState.Unchanged;
                novoLeilao.Utilizador = existingUtilizador;
            }
            if (novoLeilao.Estado.Equals("aValidar"))
            {
                _emailSenderService.SendDetails(existingUtilizador.email, "Bird Box:Onde enviar a sua peça");
            }
            _context.Leiloes.Add(novoLeilao);
            await _context.SaveChangesAsync();
        }

        public async Task<List<Leilao>> GetLeilaoByUser(string Username)
        {

            List<Leilao> l = await _context.Leiloes.ToListAsync();
            List<Leilao> final = new List<Leilao>();
            foreach (Leilao le in l)
            {
                if (le.UtilizadorUsername.Equals(Username))
                {
                    string codLeilaoToFilter = le.CodLeilao; // Replace with the actual value you're looking for

                    List<LeilaoImage> filteredImages = await _context.LeilaoImages
                        .Where(image => image.LeilaoCodLeilao == codLeilaoToFilter)
                        .ToListAsync();

                    foreach (var image in filteredImages)
                    {
                        le.Images.Add(image.ImageUrl);
                    }
                    final.Add(le);

                }

            }
            return final;
        }

        public async Task UpdateLeilaoState(Leilao leilao, string newState)
        {
            if (leilao != null)
            {
                leilao.Estado = newState;
                await _context.SaveChangesAsync();
            }
        }

        public async Task ChooseWinningBids()
        {
            List<Leilao> leiloes = await GetAllLeiloes();

            foreach (Leilao item in leiloes)
            {

                if ((item.Estado.Equals("aDecorrer") || item.Estado.Equals("aProcessar")) && item.DataFinal.CompareTo(DateTime.Now) < 0)
                {
                    await UpdateLeilaoState(item, "aProcessar");
                    List<Licitacao> licitacoes = await _licitacoes.ConsultarLicitacaoListLei(item.CodLeilao);
                    Licitacao? lMax = null;

                    foreach (Licitacao licitacao in licitacoes)
                    {
                        if (licitacao.Estado.Equals("InValida"))
                        {
                            continue;
                        }
                        if (licitacao.isWinner && licitacao.Equals("Valida"))
                        {
                            lMax = licitacao;
                            break;
                        }
                        if (lMax == null)
                        {
                            lMax = licitacao;
                            continue;
                        }
                        if(licitacao.valor > lMax.valor)
                        {
                            lMax = licitacao;
   
                        }
                        else if (licitacao.valor == lMax.valor && licitacao.timestamp.CompareTo(DateTime.Now) < 0)
                        {

                            lMax = licitacao;

                        }

                    }
                    if(lMax == null)
                    {
                        Utilizador u = await _servicoUtilizador.GetUtilizadorAux(item.UtilizadorUsername);
                        _emailSenderService.SendAuctionEndedEmail(u.email, item.Name, false);
                        await UpdateLeilaoState(item, "Terminado");
                        Console.WriteLine("BOO UOU NINGUEM QUER ISTO");
                    }
                    else
                    {
                        Console.WriteLine(lMax.codLicitacao);
                        await _licitacoes.AlterarIsWining(lMax.codLicitacao, true);
                    }

                    

                }
            }
        }

        public async Task UpdateLeilaoStateById(string codLeilao,string newState)
        {
            Leilao leilao = await _context.Leiloes.FirstOrDefaultAsync(p => p.CodLeilao.Equals(codLeilao)).ConfigureAwait(false);
            if (leilao != null)
            {
                leilao.Estado = newState;
                await _context.SaveChangesAsync();
            }
        }

        public async Task ChooseWinningBid(string codLeilao)
        {
            Leilao item = await _context.Leiloes.FirstOrDefaultAsync(p => p.CodLeilao.Equals(codLeilao)).ConfigureAwait(false);
            if ((item.Estado.Equals("aDecorrer") || item.Estado.Equals("aProcessar")) && item.DataFinal.CompareTo(DateTime.Now) < 0)
            {
                await UpdateLeilaoState(item, "aProcessar");
                List<Licitacao> licitacoes = await _licitacoes.ConsultarLicitacaoListLei(item.CodLeilao);
                Licitacao? lMax = null;

                foreach (Licitacao licitacao in licitacoes)
                {
                    if (licitacao.Estado.Equals("InValida"))
                    {
                        continue;
                    }
                    if (licitacao.isWinner && licitacao.Equals("Valida"))
                    {
                        lMax = licitacao;
                        break;
                    }
                    if (lMax == null)
                    {
                        lMax = licitacao;
                        continue;
                    }
                    if (licitacao.valor > lMax.valor)
                    {
                        lMax = licitacao;

                    }
                    else if (licitacao.valor == lMax.valor && licitacao.timestamp.CompareTo(DateTime.Now) < 0)
                    {

                        lMax = licitacao;

                    }

                }
                if (lMax == null)
                {
                    Utilizador u = await _servicoUtilizador.GetUtilizadorAux(item.UtilizadorUsername);
                    _emailSenderService.SendAuctionEndedEmail(u.email, item.Name, false);
                    await UpdateLeilaoState(item, "Terminado");
                }
                else
                {
                    Console.WriteLine(lMax.codLicitacao);
                    await _licitacoes.AlterarIsWining(lMax.codLicitacao, true);
                }



            }
        }

        public async Task UpdateLeilaoRelatorio(string codLeilao, IFormFile file)
        {
            // Get the existing Leilao
            Leilao existingLeilao = await _context.Leiloes
                .FirstOrDefaultAsync(p => p.CodLeilao.Equals(codLeilao))
                .ConfigureAwait(false);
            Console.WriteLine(codLeilao);


            if (existingLeilao != null)
            {
                Console.WriteLine("Dentro do if null");

                var fileName = $"NovaPasta/{codLeilao}_Relatorio.pdf";
                var filePath = Path.Combine(fileName);

                using (var fileStream = new FileStream(filePath, FileMode.Create))
                {
                    await file.CopyToAsync(fileStream);
                }

                // Update the URL in the Leilao entity
                existingLeilao.Relatorio = $"{fileName}";
                existingLeilao.DataFinal = DateTime.Now.AddDays(7) ;
                existingLeilao.Estado = "aDecorrer";
                existingLeilao.IsPublic = true;
                // Save changes to the database
                await _context.SaveChangesAsync();
            }
        }

        public async Task<bool> AddLeilaoWishList(Leilao leilao, string username)
        {
            Console.WriteLine("Deu para vir ate aqui");
            Utilizador existingUtilizador = await _context.Utilizadores.FindAsync(username);
            if (leilao.UtilizadorUsername.Equals(username))
            {
                return false;
            }
            Console.WriteLine("Deu para vir ate aqui2");
            WishList w = new WishList();
            w.LeilaoCodLeilao = leilao.CodLeilao;
            w.Leilao = await _context.Leiloes.FindAsync(leilao.CodLeilao);
            w.UtilizadorUsername = username;
            w.Utilizador = existingUtilizador;
            Console.WriteLine("Deu para vir ate aqui3");
            WishList t = await _context.WishLists.FirstOrDefaultAsync(p => p.UtilizadorUsername.Equals(username) && p.LeilaoCodLeilao.Equals(leilao.CodLeilao));
            Console.WriteLine("Deu para vir ate aqui4");
            if (t == null)
            {
                Console.WriteLine("Deu para vir ate aqui5");
                _context.WishLists.Add(w);
                
            }
            else
            {
                Console.WriteLine("Deu para vir ate aqui6");
                _context.WishLists.Remove(t);
                
            }
            await _context.SaveChangesAsync();
            return true;
        }
        public async Task<List<WishList>> GetLeilaoWishList(string username)
        {
          List<WishList> list = await _context.WishLists
         .Where(w => w.UtilizadorUsername.Equals(username))
         .ToListAsync();

            return list;
        }

        public async Task<bool> RemoveLeilao(string codLeilao)
        {
            Leilao l = await GetLeilao(codLeilao);

            if (l.Estado.Equals("Terminado"))
            {
                return false;
            }
            else
            {
                Console.WriteLine("A eliminar...");
                List<WishList> listWish = await _context.WishLists
                     .Where(w => w.LeilaoCodLeilao.Equals(codLeilao))
                     .ToListAsync();

                List<Licitacao> Licitacoes = await _licitacoes.ConsultarLicitacaoListLei(codLeilao);

                List<LeilaoImage> filteredImages = await _context.LeilaoImages
                       .Where(image => image.LeilaoCodLeilao.Equals(codLeilao))
                       .ToListAsync();

                foreach (Licitacao item in Licitacoes)
                {
                    _context.Licitacoes.Remove(item);
                    
                }
                foreach (WishList item in listWish)
                {
                    _context.WishLists.Remove(item);

                }
                foreach (LeilaoImage item in filteredImages)
                {
                    _context.LeilaoImages.Remove(item);

                }
                _context.Leiloes.Remove(l);
                await _context.SaveChangesAsync();
                return true;
            }


           
        }
    }
}
