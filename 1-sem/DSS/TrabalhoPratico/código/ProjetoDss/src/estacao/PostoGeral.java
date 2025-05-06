package estacao;

import estacao.business.*;
import estacao.ui.PostoController;
import estacao.ui.PostoView;

import java.time.LocalDateTime;

public class PostoGeral {

    public static void main(String[] args) {

        EstacaoFacade e = new EstacaoFacade(1,LocalDateTime.now().plusHours(5));
        PostoView v = new PostoView();
        PostoController c = new PostoController(e,v);
        c.handleMenu();
    }
}