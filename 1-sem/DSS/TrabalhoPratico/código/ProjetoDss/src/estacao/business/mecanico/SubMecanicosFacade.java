package estacao.business.mecanico;

import estacao.business.mecanico.ISubMecanicos;
import estacao.business.mecanico.Mecanico;
import estacao.data.MecanicoDAO;

import java.util.List;

public class SubMecanicosFacade implements ISubMecanicos {
    private final MecanicoDAO mecanicos;
    public SubMecanicosFacade (){
        mecanicos = MecanicoDAO.getInstance();
    }
    @Override
    public void removeMecanico(int idMecanico) {

    }

    @Override
    public void verificaCompetencias(int idMecanico) {

    }

    @Override
    public void iniciaTurno(int idMecanico) {

    }

    @Override
    public void acabaTurno(int idMecanico) {

    }

    @Override
    public void registaMecanico(String nome) {

    }

    @Override
    public List<Mecanico> getMecanicos() {
        return null;
    }
}
