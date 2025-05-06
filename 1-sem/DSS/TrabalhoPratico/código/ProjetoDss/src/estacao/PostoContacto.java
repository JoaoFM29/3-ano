package estacao;

import estacao.business.EstacaoFacade;
import estacao.ui.ControllerSecretaria;
import estacao.ui.ViewSecretaria;

import java.time.LocalDateTime;

public class PostoContacto {

    public static void main(String[] args) {

        EstacaoFacade e = new EstacaoFacade(1, LocalDateTime.now().plusHours(5));
        ViewSecretaria v = new ViewSecretaria();
        ControllerSecretaria c = new ControllerSecretaria(e,v);
        c.handleMenu();
    }
}
