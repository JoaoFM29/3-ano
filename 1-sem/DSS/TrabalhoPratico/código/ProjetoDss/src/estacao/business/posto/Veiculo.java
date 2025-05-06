package estacao.business.posto;

import java.util.List;

public class Veiculo {
    private String matricula;

    private String caracterizacao;
    List<Integer> fichaVeiculo;
    List<Motor> motor;
    public Veiculo(String matricula, String caracterizacao, List<Integer> fichaVeiculo, List<Motor> motor) {
        this.matricula = matricula;
        this.caracterizacao = caracterizacao;
        this.fichaVeiculo = fichaVeiculo;
        this.motor = motor;
    }
    public String getMatricula() {
        return matricula;
    }

    public void setMatricula(String matricula) {
        this.matricula = matricula;
    }

    public String getCaracterizacao() {
        return caracterizacao;
    }

    public void setCaracterizacao(String caracterizacao) {
        this.caracterizacao = caracterizacao;
    }

    public List<Integer> getFichaVeiculo() {
        return fichaVeiculo;
    }

    public void setFichaVeiculo(List<Integer> fichaVeiculo) {
        this.fichaVeiculo = fichaVeiculo;
    }

    public List<Motor> getMotor() {
        return motor;
    }

    public void setMotor(List<Motor> motor) {
        this.motor = motor;
    }
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Matricula: ").append(matricula).append("\n");
        sb.append("Caracterizacao: ").append(caracterizacao).append("\n");
        sb.append("Ficha do Veiculo: ").append(fichaVeiculo).append("\n");

        if (motor != null) {
            sb.append("Motor: \n");
            for (Motor m : motor) {
                sb.append("- ").append(m).append("\n");
            }
        } else {
            sb.append("Motor: N/A\n");
        }

        return sb.toString();
    }

}
