package classes;
import java.util.List;

public class Leilao {
    private String codLeilao;
    private String codUtilizador;
    private String descricao;
    private List<String> media; // Lista de strings das fotografias usadas no leilao
    private float valorMinimo;
    private String relatorio;
    private String estado;
    private List<String> licitacoes; // Lista dos codigos das licitacoes

    public Leilao(String codLeilao, String codUtilizador, String descricao, List<String> media,
                  float valorMinimo, String relatorio, String estado, List<String> licoes) {
        this.codLeilao = codLeilao;
        this.codUtilizador = codUtilizador;
        this.descricao = descricao;
        this.media = media;
        this.valorMinimo = valorMinimo;
        this.relatorio = relatorio;
        this.estado = estado;
        this.licitacoes = licoes;
    }

    public String getCodLeilao() {
        return codLeilao;
    }

    public void setCodLeilao(String codLeilao) {
        this.codLeilao = codLeilao;
    }

    @Override
    public String toString() {
        return "Leilao{" +
                "codLeilao='" + codLeilao + '\'' +
                ", codUtilizador='" + codUtilizador + '\'' +
                ", descricao='" + descricao + '\'' +
                ", media=" + media +
                ", valorMinimo=" + valorMinimo +
                ", relatorio='" + relatorio + '\'' +
                ", estado='" + estado + '\'' +
                ", licoes=" + licitacoes +
                '}';
    }
}

