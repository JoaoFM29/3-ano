package estacao.business.posto;

import java.util.Objects;

public class Servico {
	private int idServico;
	private String designacao;
	private float duracao;
	private float preco;

	public Servico(int idServico, String designacao, float duracao, float preco) {
		this.idServico = idServico;
		this.designacao = designacao;
		this.duracao = duracao;
		this.preco = preco;
	}
	public int getIdServico() {
		return idServico;
	}

	public void setIdServico(int idServico) {
		this.idServico = idServico;
	}

	public String getDesignacao() {
		return designacao;
	}

	public void setDesignacao(String designacao) {
		this.designacao = designacao;
	}

	public float getDuracao() {
		return duracao;
	}

	public void setDuracao(float duracao) {
		this.duracao = duracao;
	}

	public float getPreco() {
		return preco;
	}

	public void setPreco(float preco) {
		this.preco = preco;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (o == null || getClass() != o.getClass()) return false;
		Servico servico = (Servico) o;
		return idServico == servico.idServico && Float.compare(servico.duracao, duracao) == 0 && Float.compare(servico.preco, preco) == 0 && Objects.equals(designacao, servico.designacao);
	}

	@Override
	public String toString() {
		return "estacao.business.posto.Servico{" +
				"idServico=" + idServico +
				", designacao='" + designacao + '\'' +
				", duracao=" + duracao +
				", preco=" + preco +
				'}';
	}
}