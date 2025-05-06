package estacao.ui;

import estacao.business.posto.Posto;
import estacao.business.posto.Servico;

import java.util.List;
import java.util.Map;

public class PostoView {

    public PostoView() {
    }

    public void showAnotherMenu() {
        System.out.println("===== Another Menu =====");
        System.out.println("1 - Registar Serviço");
        System.out.println("2 - Concluir Serviço");
        System.out.println("3 - Obter Lista de Tarefas");
        System.out.println("4 - Sair");
        System.out.print("Escolha uma opção: ");
    }
    public void showTarefas(Map<String, List<Servico>> tarefas){

        if (tarefas != null && !tarefas.isEmpty()) {
            System.out.println("Tarefas do Mecânico:");
            for (Map.Entry<String, List<Servico>> entry : tarefas.entrySet()) {
                System.out.println("Matrícula: " + entry.getKey());
                System.out.println("Serviços:");
                for (Servico servico : entry.getValue()) {
                    System.out.println("ID: " + servico.getIdServico() + ", Descrição: " + servico.getDesignacao());
                }
            }
        } else {
            System.out.println("Nenhuma tarefa encontrada para o mecânico com o ID informado.");
        }

    }

    public void showPosto(Posto p){

        System.out.println("Ficha atualizada com sucesso");
        System.out.println("Cliente deve dirigir se para o posto " + p.getIdPosto());

    }

    public void fichaAtualizada() {

        System.out.println("Ficha do veículo atualizada!");
    }

    public void showPostos(List<Posto> pl) {
        System.out.println("Cliente deve dirigir se a um destes postos");
        for (Posto p:pl
             ) {
            System.out.println("Posto " + p.getIdPosto());
        }
    }

    public void showSucessoMensagem(int nif) {
        System.out.println("Mensagem enviada ao cliente:  " + nif);
    }
}
