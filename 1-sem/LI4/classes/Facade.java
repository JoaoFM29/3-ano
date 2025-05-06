package classes;

import java.util.*;
import java.util.HashMap;
import java.util.Map;

public class Facade {
    Map <String, Utilizador> utilizadores = new HashMap<>();
    Map <String, Leilao> leiloes = new HashMap<>();

    public boolean validaUser(String codUtilizador){
        return utilizadores.containsKey(codUtilizador);
    }

    public void removeUser(String codUtilizador){
        utilizadores.remove(codUtilizador);
    }

    public List<Utilizador> imprimeUsers(){
        return new ArrayList<Utilizador>(utilizadores.values());
    }
}
