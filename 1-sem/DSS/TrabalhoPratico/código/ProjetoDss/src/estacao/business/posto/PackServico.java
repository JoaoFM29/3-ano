package estacao.business.posto;

import java.util.List;

public class PackServico {

	private String nome;


	private int Id;
	private List<Servico> sv;

	public PackServico(int id,String nome, List<Servico> sv) {
		this.nome = nome;
		this.sv = sv;
		this.Id = id;
	}
	public int getId() {
		return Id;
	}

	public void setId(int id) {
		Id = id;
	}
	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public List<Servico> getSv() {
		return sv;
	}

	public void setServicos(List<Servico> sv) {
		this.sv = sv;
	}

	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("ID: ").append(Id).append("\n");
		sb.append("Nome: ").append(nome).append("\n");
		sb.append("Servicos do Pack:\n");

		if (sv != null) {
			for (Servico servico : sv) {
				sb.append("- ").append(servico).append("\n");
			}
		} else {
			sb.append("Nenhum serviço associado a este pack.\n");
		}

		return sb.toString();
	}


}