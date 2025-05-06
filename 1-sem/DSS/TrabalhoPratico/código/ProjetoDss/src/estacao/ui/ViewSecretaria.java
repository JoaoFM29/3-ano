package estacao.ui;

import estacao.business.posto.Posto;

public class ViewSecretaria {

    public ViewSecretaria() {
    }

    public void showMainMenu() {
        System.out.println("===== Menu Principal =====");
        System.out.println("1 - Adicionar Serviço ao Veículo");
        System.out.println("2 - Sair");
        System.out.print("Escolha uma opção: ");
    }

    public void showPosto(Posto p){

        System.out.println("Ficha atualizada com sucesso");
        System.out.println("Cliente deve dirigir se para o posto " + p.getIdPosto());

    }
}






