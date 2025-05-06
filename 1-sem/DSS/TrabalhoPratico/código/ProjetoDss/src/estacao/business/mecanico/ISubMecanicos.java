package estacao.business.mecanico;

import java.util.List;

public interface ISubMecanicos {

	/**
	 * 
	 * @param idMecanico
	 */
	void removeMecanico(int idMecanico);

	/**
	 * 
	 * @param idMecanico
	 */
	void verificaCompetencias(int idMecanico);

	/**
	 * 
	 * @param idMecanico
	 */
	void iniciaTurno(int idMecanico);

	/**
	 * 
	 * @param idMecanico
	 */
	void acabaTurno(int idMecanico);

	/**
	 * 
	 * @param nome
	 */
	void registaMecanico(String nome);

	List<Mecanico> getMecanicos();

}