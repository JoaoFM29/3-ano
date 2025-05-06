package estacao.business.posto;

import estacao.business.MecanicoNaoPertenceException;
import estacao.business.NaoTemDisponibilidadeException;
import estacao.business.VeiculoNaoPodeException;

import java.util.List;
import java.util.Map;

public interface ISubFuncPostos {

    public void registaPosto(String idServico);
    public void registaServicoPosto(String idServico,int idPosto);
    public void removePosto(int idPosto);
    public void addMecanicoPosto(int idMecanico1,int idMecanico2,int idPosto);
    public void addServicoSistema(String designacao,String tipo,float duracao);
    public void atualizaFichaVeiculoNovaIntervencao(String matricula, int idServico,int  nif) throws VeiculoNaoPodeException;;
    public List<Posto> getPostos();
    public List<Servico> getServicosDisponiveis();
    public void addPackServicoSistema(List<Integer> servs,String nome);
    public void registaCliente(String nome,int contacto,String email);
    public Posto agendarServico(String matricula, int idServico) throws NaoTemDisponibilidadeException;
    public boolean atualizaFichaVeiculoConcluido(String matricula, int idServico, int  nif,int idPosto);
    public void atualizaFichaVeiculoCheckUp(String matricula,List<Integer>idServico,int nif) throws VeiculoNaoPodeException;

    public boolean avisarCliente(int nif);
    public Map<String,List<Servico>> getListaTarefas(int idMecanico, int  idPosto) throws MecanicoNaoPertenceException;
}
