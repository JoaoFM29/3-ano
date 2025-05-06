using System;
using System.Collections.Generic;

public class Facade
{
    /*
    private Dictionary<string, Utilizador> utilizadores = new Dictionary<string, Utilizador>();
    private Dictionary<string, Leilao> leiloes = new Dictionary<string, Leilao>();
    private Dictionary<string, Licitacao> licitacoes = new Dictionary<string, Licitacao>();

    public bool ValidaUser(string codUtilizador)
    {
        return utilizadores.ContainsKey(codUtilizador);
    }

    public void RemoveUser(string codUtilizador)
    {
        utilizadores.Remove(codUtilizador);
    }

    public List<Utilizador> ImprimeUsers()
    {
        return new List<Utilizador>(utilizadores.Values);
    }
    public void updateDados (string codUtilizador, string password, DateTime dataNascimento, string metodoPagamento,
                        string indicativo, string numeroTelemovel, string email, string numeroPorta,
                        string rua, string localidade, string codigoPostal, string cc, List<string> encomendas)
    {
        utilizadores[codUtilizador].password = password;
        utilizadores[codUtilizador].dataNascimento = dataNascimento;
        utilizadores[codUtilizador].metodoPagamento = metodoPagamento;
        utilizadores[codUtilizador].indicativo=indicativo;
        utilizadores[codUtilizador].numeroTelemovel=numeroTelemovel;
        utilizadores[codUtilizador].email=email;
        utilizadores[codUtilizador].numeroPorta=numeroPorta;
        utilizadores[codUtilizador].rua=rua;
        utilizadores[codUtilizador].localidade=localidade;
        utilizadores[codUtilizador].codigoPostal=codigoPostal;
        utilizadores[codUtilizador].cc=cc;
        utilizadores[codUtilizador].encomendas=encomendas;
        
    }
    // get lista de leiloes ordenado por mais antigo a cabeça 
    public List<Leilao> GetLeiloes()
    {
        List<Leilao> leiloesOrdenados = new List<Leilao>(leiloes.Values);
        leiloesOrdenados.Sort((x, y) => DateTime.Compare(x.dataCriacao, y.dataCriacao));
        return leiloesOrdenados;
    }
    //registaUser(string codUtilizador, string password, DateTime dataNascimento, string metodoPagamento, string indicativo, string numeroTelemovel, string email, string numeroPorta,string rua, string localidade, string codigoPostal, string cc)
    //Validar qualidade de fotos pela resolucao e tamanho dado o caminho
    //atualizaEstado( codLeilao : string ) : boolean
    //apresentaLeilao(codLeilao : string ) : Leilao
    //fornecefilterLeiloes(FILTROS, leiloes::  List (leilao)) : List(Leilao)
    //validaLicitacao(codLeilao : string, codutilizador : string, valorLicitacao : float) : boolean
    //registaLicitacao(codLicitacao : string ) : booleam
    //removerLicitacao(codLicitacao :: string) :: boolean
    //registaRelatorio(codLeiloes :: string,  relatorio :: [] byte ) :: boolean
    //forneceLeiloes(codUtilizador :: string, estado :: string) :: List(Leilao)
    //addWishList(codUtilizador :: string, codLeilao) :: boolean
    //wishList(codUtilizador :: string) :: List (Leilao)
    //removeWishList(codUtilizador :: string, codLeilao :: string) ::boolean
    //
    */
}
