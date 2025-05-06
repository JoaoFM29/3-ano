package classes;
import java.util.List;
import java.util.Date;

public class Utilizador {
    private String codUtilizador;
    private String password;
    private Date dataNascimento;
    private String metodoPagamento;
    private String indicativo;
    private String numeroTelemovel;
    private String email;
    private String numeroPorta;
    private String rua;
    private String localidade;
    private String codigoPostal;
    private String cc;
    private List<String> encomendas; //lista de codigos de encomendas feitas

    public Utilizador(String codUtilizador, String password, Date dataNascimento, String metodoPagamento,
                      String indicativo, String numeroTelemovel, String email, String numeroPorta,
                      String rua, String localidade, String codigoPostal, String cc, List<String> encomendas) {
        this.codUtilizador = codUtilizador;
        this.password = password;
        this.dataNascimento = dataNascimento;
        this.metodoPagamento = metodoPagamento;
        this.indicativo = indicativo;
        this.numeroTelemovel = numeroTelemovel;
        this.email = email;
        this.numeroPorta = numeroPorta;
        this.rua = rua;
        this.localidade = localidade;
        this.codigoPostal = codigoPostal;
        this.cc = cc;
        this.encomendas = encomendas;
    }

    public String getCodUtilizador() {
        return codUtilizador;
    }

    public void setCodUtilizador(String codUtilizador) {
        this.codUtilizador = codUtilizador;
    }

    @Override
    public String toString() {
        return "Utilizador{" +
                "codUtilizador='" + codUtilizador + '\'' +
                ", password='" + password + '\'' +
                ", dataNascimento=" + dataNascimento +
                ", metodoPagamento='" + metodoPagamento + '\'' +
                ", indicativo='" + indicativo + '\'' +
                ", numeroTelemovel='" + numeroTelemovel + '\'' +
                ", email='" + email + '\'' +
                ", numeroPorta='" + numeroPorta + '\'' +
                ", rua='" + rua + '\'' +
                ", localidade='" + localidade + '\'' +
                ", codigoPostal='" + codigoPostal + '\'' +
                ", cc='" + cc + '\'' +
                ", encomendas=" + encomendas +
                '}';
    }
}
