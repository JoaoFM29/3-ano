package classes;
public class Encomenda {
    private String codEncomenda;
    private String codLeilao;
    private String numeroSeguimento;

    public Encomenda(String codEncomenda, String codLeilao, String numeroSeguimento) {
        this.codEncomenda = codEncomenda;
        this.codLeilao = codLeilao;
        this.numeroSeguimento = numeroSeguimento;
    }

    public String getCodEncomenda() {
        return codEncomenda;
    }

    public void setCodEncomenda(String codEncomenda) {
        this.codEncomenda = codEncomenda;
    }

    @Override
    public String toString() {
        return "Encomenda{" +
                "codEncomenda='" + codEncomenda + '\'' +
                ", codLeilao='" + codLeilao + '\'' +
                ", numeroSeguimento='" + numeroSeguimento + '\'' +
                '}';
    }
}

