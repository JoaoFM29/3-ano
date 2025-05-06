package estacao.ui;

import estacao.business.*;
import estacao.business.posto.Posto;
import estacao.business.posto.Servico;


import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class PostoController {
    private PostoView view;
    private EstacaoFacade postoFacade;
    private Scanner scanner;

    public PostoController(EstacaoFacade postoFacade, PostoView v) {
        this.postoFacade = postoFacade;
        this.view = v;
        this.scanner = new Scanner(System.in);
    }

    public void handleMenu() {
        boolean running = true;

        while (running) {
            view.showAnotherMenu();
            int option = readOption();

            switch (option) {
                case 1:
                    registarServico();
                    break;
                case 2:
                    concluirServico();
                    break;
                case 3:
                    verListaDeServico();
                    break;
                case 4:
                    running = false;
                    break;
                default:
                    System.out.println("Opção inválida. Tente novamente.");
            }
        }
    }



    private int readOption() {
        int option = -1;
        try {
            option = scanner.nextInt();
            scanner.nextLine();
        } catch (Exception e) {
            System.out.println("Erro ao ler a opção. Certifique-se que inseriu um número.");
            scanner.next();
        }
        return option;
    }
    private void verListaDeServico() {
        System.out.print("Insira o ID do Mecânico: ");
        int idMecanico = scanner.nextInt();
        scanner.nextLine();
        System.out.print("Insira o ID do Posto: ");
        int idPosto = scanner.nextInt();
        scanner.nextLine();

        try {
            Map<String, List<Servico>> tarefas = postoFacade.getListaTarefas(idMecanico, idPosto);
            view.showTarefas(tarefas);

        } catch (MecanicoNaoPertenceException e) {
            System.out.println("Erro,Não autorizado");
        } catch (Exception e) {
            System.out.println("Ocorreu um erro ao processar as tarefas");
        }
    }

    private void registarServico(){ // por fazer

        System.out.print("Insira a Matrícula do Veículo: ");
        String matricula = scanner.next();
        System.out.print("Insira o ID do Serviço: ");
        int servicoId = scanner.nextInt();
        scanner.nextLine();
        System.out.print("Insira o NIF do Cliente: ");
        int nif = scanner.nextInt();
        scanner.nextLine();


        try {
            postoFacade.atualizaFichaVeiculoNovaIntervencao(matricula, servicoId, nif);
            Posto p = postoFacade.agendarServico(matricula,servicoId);
            view.showPosto(p);
        } catch (NaoTemDisponibilidadeException e) {
            System.out.println("Erro ao atualizar a ficha do veículo: " + e.getMessage());
        }catch ( VeiculoNaoPodeException e){
            System.out.println("Erro, serviço não pode ser realizado neste veículo");
        }


    }

    private void concluirServico(){ // por fazer

        System.out.print("Insira a Matrícula do Veículo: ");
        String matricula = scanner.next();
        System.out.print("Insira o ID do Serviço: ");
        int servicoId = scanner.nextInt();
        scanner.nextLine();
        System.out.print("Insira o NIF do Cliente: ");
        int nif = scanner.nextInt();
        scanner.nextLine();
        System.out.print("Insira o Id do Posto: ");
        int idP = scanner.nextInt();
        scanner.nextLine();

        boolean acabou = postoFacade.atualizaFichaVeiculoConcluido(matricula, servicoId, nif,idP);


        if (servicoId == 0){ // caso de ser um check up

            System.out.print("Insira o ID do(s) Serviço(s) separado(s) por ',' : ");
            String l = scanner.next();
            String[] st = l.split(",");
            List<Integer> servicoIds = new ArrayList<>();
            for (String i : st){
                int aux = Integer.parseInt(i);
                servicoIds.add(aux);
            }
            try {
                postoFacade.atualizaFichaVeiculoCheckUp(matricula, servicoIds, nif);
                Posto P = null;
                boolean flag =false;
                for ( int id : servicoIds){

                    if (!flag) {
                        P = postoFacade.agendarServico(matricula, id);
                        flag = true;
                    }else{
                        postoFacade.agendarServico(matricula, id);
                    }
                }
                view.showPosto(P);
            } catch (NaoTemDisponibilidadeException e) {
                System.out.println("Erro ao atualizar a ficha do veículo");
            }catch ( VeiculoNaoPodeException e){

                System.out.println("Erro, algum dado inválido ou cliente não registado");
            }

        }else {
            if(acabou){
                System.out.println("A ficha está vazia");
                System.out.print("Requere Sms (s/n): ");
                String s = scanner.next();

                if (s.equals("s")){
                    postoFacade.avisarCliente(nif);
                    view.showSucessoMensagem(nif);
                }

            }else {

                List<Posto> p = postoFacade.nextPosto(matricula);
                view.showPostos(p);

            }

        }

    }

}
