using BirdBoxFull.Shared;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

public class Leilao
{
    [Key]
    public string CodLeilao { get; set; } = Guid.NewGuid().ToString();
    public string UtilizadorUsername { get; set; }
    public Utilizador Utilizador { get; set; }
    public string Descricao { get; set; }
    public string Relatorio { get; set; }
    public string Estado { get; set; }

    [NotMapped]
    public List<string> Images { get; set; } = new List<string>();
    public string Name { get; set; }
    public decimal EntryPrice { get; set; }
    public string Location { get; set; }
    public bool IsPublic { get; set; }
    public DateTime DataFinal { get; set; }
    public List<Licitacao> Licitacoes { get; set; }
    public Encomenda? Encomenda { get; set; }
    public List<WishList> WishLists { get; set; }

    // Parameterized constructor
    public Leilao(string codLeilao, string codUtilizador, string descricao,
                  string relatorio, string estado,
                  List<string> images, string name, decimal entryPrice, string location, bool isPublic, DateTime dataFinal)
    {
        CodLeilao = codLeilao;
        UtilizadorUsername = codUtilizador;
        Descricao = descricao;
        Relatorio = relatorio;
        Estado = estado;
        Images = images;
        Name = name;
        EntryPrice = entryPrice;
        Location = location;
        IsPublic = isPublic;
        DataFinal = dataFinal;
        Licitacoes = new List<Licitacao>();
        WishLists = new List<WishList>();
    }

    public Leilao(string codUtilizador, string descricao,
                  string relatorio, string estado,
                  List<string> images, string name, decimal entryPrice, string location, bool isPublic, DateTime dataFinal) {


        CodLeilao = Guid.NewGuid().ToString();
        UtilizadorUsername = codUtilizador;
        Descricao = descricao;
        Relatorio = relatorio;
        Estado = estado;
        Images = images;
        Name = name;
        EntryPrice = entryPrice;
        Location = location;
        IsPublic = isPublic;
        DataFinal = dataFinal;
        Licitacoes = new List<Licitacao>();
        WishLists = new List<WishList>();


    }
    public Leilao() { }
}


