package estacao.business.posto;

public class Motor {

	private String modeloMotor;

	public Motor(String idMotor) {
		this.modeloMotor = idMotor;
	}

	public String getIdMotor() {
		return modeloMotor;
	}

	public void setIdMotor(String idMotor) {
		this.modeloMotor = idMotor;
	}

	@Override
	public String toString() {
		return "Modelo do Motor: " + modeloMotor;
	}

}