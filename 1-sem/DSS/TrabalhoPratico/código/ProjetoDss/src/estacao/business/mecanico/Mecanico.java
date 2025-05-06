package estacao.business.mecanico;

public class Mecanico {

	private String nome;
	private int idMecanico;

	public Mecanico(String nome, int idMecanico) {
		this.nome = nome;
		this.idMecanico = idMecanico;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public int getIdMecanico() {
		return idMecanico;
	}

	public void setIdMecanico(int idMecanico) {
		this.idMecanico = idMecanico;
	}

	public String toString() {
		return "Nome do Mecânico: " + nome + ", ID do Mecânico: " + idMecanico;
	}

}