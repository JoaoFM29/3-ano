using System;
using System.ComponentModel.DataAnnotations;

namespace BirdBoxFull.Shared
{
    public class Licitacao
    {
        [Key]
        public string codLicitacao { get; set; } = Guid.NewGuid().ToString();
        public string LeilaoCodLeilao { get; set; }
        public Leilao Leilao { get; set; }
        public string UtilizadorUsername { get; set; }
        public Utilizador Utilizador {  get; set; }
        public float valor { get; set; }
        public DateTime timestamp { get; set; }
        public bool isWinner { get; set; }

        public string Estado { get; set; }

        public Licitacao()
        {

        }
        public Licitacao(string LeilaoCodLeilao, Leilao Leilao, string UtilizadorUsername, Utilizador Utilizador, float valor, DateTime timestamp, bool isWinner, string Estado)
        {
            this.Leilao = Leilao;
            this.LeilaoCodLeilao = LeilaoCodLeilao;
            this.UtilizadorUsername = UtilizadorUsername;
            this.Utilizador = Utilizador;
            this.timestamp = timestamp;
            this.isWinner = isWinner;
            this.valor = valor;
            this.codLicitacao = Guid.NewGuid().ToString();
            this.Estado = Estado;


        }
      



    }

    

}
