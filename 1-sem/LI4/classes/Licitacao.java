package classes;
import java.time.LocalDate;

public class Licitacao {
    private String codLicitacao;
    private String codLeilao;
    private String codUtilizador;
    private float valor;
    private LocalDate timestamp;

    public Licitacao(String codLicitacao, String codLeilao, String codUtilizador, float valor, LocalDate timestamp) {
        this.codLicitacao = codLicitacao;
        this.codLeilao = codLeilao;
        this.codUtilizador = codUtilizador;
        this.valor = valor;
        this.timestamp = timestamp;
    }

    public String getCodLicitacao() {
        return codLicitacao;
    }

    public void setCodLicitacao(String codLicitacao) {
        this.codLicitacao = codLicitacao;
    }

    @Override
    public String toString() {
        return "Licitacao{" +
                "codLicitacao='" + codLicitacao + '\'' +
                ", codLeilao='" + codLeilao + '\'' +
                ", codUtilizador='" + codUtilizador + '\'' +
                ", valor=" + valor +
                ", timestamp=" + timestamp +
                '}';
    }
}
