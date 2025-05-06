package estacao.business;

import java.time.LocalDateTime;

public interface IEstacao {

	LocalDateTime getHorariOficina();
	void defineHorariOficina(int idOficina, LocalDateTime dataF);



}