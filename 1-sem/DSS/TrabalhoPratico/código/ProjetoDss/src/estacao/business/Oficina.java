package estacao.business;

import java.time.LocalDateTime;

public class Oficina {

    private int idOficina;

    private LocalDateTime dataF;

    public Oficina(int idOficina, LocalDateTime dataF) {
        this.idOficina = idOficina;
        this.dataF = dataF;
    }
    public int getIdOficina() {
        return idOficina;
    }

    public void setIdOficina(int idOficina) {
        this.idOficina = idOficina;
    }

    public LocalDateTime getDataF() {
        return dataF;
    }

    public void setDataF(LocalDateTime dataF) {
        this.dataF = dataF;
    }
}
