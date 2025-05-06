using System.ComponentModel.DataAnnotations;

namespace BirdBoxFull.Shared { 
public class Encomenda
{
    [Key]
    public string codEncomenda { get; set; } = Guid.NewGuid().ToString();
    public string LeilaoCodLeilao { get; set; }
    public Leilao Leilao { get; set; }
    public string UtilizadorUsername { get; set; }
    public Utilizador Utilizador { get; set; }
    public string numeroSeguimento { get; set; }

    public Encomenda(string LeilaoCodLeilao, string UtilizadorUsername, string numeroSeguimento)
    {
        
        this.LeilaoCodLeilao = LeilaoCodLeilao;
        this.UtilizadorUsername = UtilizadorUsername;
        this.numeroSeguimento = numeroSeguimento;
    }

    public Encomenda()
    {

    }


  

}
}
