package estacao.ui;

import estacao.business.EstacaoFacade;
import estacao.business.NaoTemDisponibilidadeException;
import estacao.business.VeiculoNaoPodeException;
import estacao.business.posto.Posto;

import java.util.Scanner;

public class ControllerSecretaria {

    private EstacaoFacade model;
    private ViewSecretaria view;
    private Scanner scanner;

    public ControllerSecretaria(EstacaoFacade postoFacade, ViewSecretaria vm) {

        this.model = postoFacade;
        this.view = vm;
        this.scanner = new Scanner(System.in);
    }

    public void handleMenu() {
        boolean running = true;

        while (running) {
            view.showMainMenu();
            int option = readOption();

            switch (option) {
                case 1:
                    addServiceToVehicle();
                    break;
                case 2:
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
        } catch (Exception e) {
            System.out.println("Erro ao ler a opção. Certifique-se que inseriu um número.");
            scanner.next();
        }
        return option;
    }

    private void addServiceToVehicle() {
        System.out.print("Insere o ID do Serviço: ");
        int serviceId = scanner.nextInt();
        System.out.print("Insere a Matricula do Veículo: ");
        String matricula = scanner.next();
        System.out.print("Insere o NIF do Cliente: ");
        int nif = scanner.nextInt();

        try {
            model.atualizaFichaVeiculoNovaIntervencao(matricula, serviceId, nif);
            Posto p = model.agendarServico(matricula,serviceId);
            view.showPosto(p);
        } catch (NaoTemDisponibilidadeException e) {
            System.out.println("Não é possível Agendar o serviço para hoje!" + e.getMessage());
        }
        catch ( VeiculoNaoPodeException e){
            System.out.println("Erro, serviço não pode ser realizado neste veículo");
        }
    }
}
