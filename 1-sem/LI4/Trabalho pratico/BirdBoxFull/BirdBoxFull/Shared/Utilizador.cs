using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace BirdBoxFull.Shared
{
    public class Utilizador
    {
        [Key]
        public string Username { get; set; }
        public string Password { get; set; }
        public string Nome { get; set; }
        public string indicativo { get; set; }
        public string numeroTelemovel { get; set; }
        public string email { get; set; }
        public string numeroPorta { get; set; }
        public string rua { get; set; }
        public string localidade { get; set; }
        public string codigoPostal { get; set; }
        public string cc { get; set; }
        public List<Licitacao> Licitacoes { get; set; }
        public List<Encomenda> Encomendas { get; set; }
        public List<WishList> WishLists { get; set; }
        public string StripeId { get; set; }

        public string AccountStripeId { get; set; }





        public Utilizador(string codUtilizador, string password, string Nome,
                            string indicativo, string numeroTelemovel, string email, string numeroPorta,
                            string rua, string localidade, string codigoPostal, string cc)
        {
            this.Username = codUtilizador;
            this.Password = password;
            this.Nome = Nome;
            this.indicativo = indicativo;
            this.numeroTelemovel = numeroTelemovel;
            this.email = email;
            this.numeroPorta = numeroPorta;
            this.rua = rua;
            this.localidade = localidade;
            this.codigoPostal = codigoPostal;
            this.cc = cc;
            
       
        }
        public Utilizador()
        {
            this.Username = string.Empty;
            this.Password = string.Empty;
            this.Nome = string.Empty;
            this.indicativo = string.Empty;
            this.numeroTelemovel = string.Empty;
            this.email = string.Empty;
            this.numeroPorta = string.Empty;
            this.rua = string.Empty;
            this.localidade = string.Empty;
            this.codigoPostal = string.Empty;
            this.cc = string.Empty;
            Licitacoes = new List<Licitacao>();
            Encomendas = new List<Encomenda>();
            WishLists = new List<WishList>();
            this.StripeId = string.Empty;
            this.AccountStripeId = string.Empty;

        }





    }
}

