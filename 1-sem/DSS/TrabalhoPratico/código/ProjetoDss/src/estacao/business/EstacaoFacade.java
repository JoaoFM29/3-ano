package estacao.business;

import estacao.business.mecanico.ISubMecanicos;
import estacao.business.mecanico.Mecanico;
import estacao.business.mecanico.SubMecanicosFacade;
import estacao.business.posto.ISubFuncPostos;
import estacao.business.posto.Posto;
import estacao.business.posto.Servico;
import estacao.business.posto.SubFuncPostosFacade;

import java.time.LocalDateTime;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class EstacaoFacade implements IEstacao, ISubMecanicos, ISubFuncPostos {

    private SubFuncPostosFacade postos_manager;

    private SubMecanicosFacade mecanicos_manager;

    private Oficina oficinas;

    public EstacaoFacade(int id, LocalDateTime date){
        oficinas = new Oficina(1,date);
        mecanicos_manager = new SubMecanicosFacade();
        postos_manager = new SubFuncPostosFacade(oficinas);
    }
    @Override
    public LocalDateTime getHorariOficina() {
        return null;
    }

    @Override
    public void defineHorariOficina(int idOficina, LocalDateTime dataF) {

    }

    @Override
    public void registaPosto(String idServico) {

    }

    @Override
    public void registaServicoPosto(String idServico, int idPosto) {

    }

    @Override
    public void removePosto(int idPosto) {

    }

    @Override
    public void addMecanicoPosto(int idMecanico1, int idMecanico2, int idPosto) {

    }

    @Override
    public void addServicoSistema(String designacao, String tipo, float duracao) {

    }

    @Override
    public void atualizaFichaVeiculoNovaIntervencao(String matricula, int idServico, int nif) throws VeiculoNaoPodeException {

        postos_manager.atualizaFichaVeiculoNovaIntervencao(matricula,idServico,nif);

    }

    @Override
    public List<Posto> getPostos() {
        return null;
    }

    @Override
    public List<Servico> getServicosDisponiveis() {
        return null;
    }

    @Override
    public void addPackServicoSistema(List<Integer> servs, String nome) {

    }

    @Override
    public void registaCliente(String nome, int contacto, String email) {

    }

    @Override
    public Posto agendarServico(String matricula, int idServico) throws NaoTemDisponibilidadeException{
        return postos_manager.agendarServico(matricula, idServico);
    }

    @Override
    public boolean atualizaFichaVeiculoConcluido(String matricula, int idServico, int nif,int idPosto) { // excessão a ser implementada
        return postos_manager.atualizaFichaVeiculoConcluido(matricula,idServico,nif,idPosto);
    }

    @Override
    public void atualizaFichaVeiculoCheckUp(String matricula, List<Integer> idServico, int nif) throws VeiculoNaoPodeException {
        postos_manager.atualizaFichaVeiculoCheckUp(matricula,idServico,nif);
    }

    @Override
    public boolean avisarCliente(int nif) {
       return postos_manager.avisarCliente(nif);
    }

    @Override
    public Map<String,List<Servico>> getListaTarefas(int idMecanico, int idPosto) throws MecanicoNaoPertenceException { //exceção a ser implementada
        return postos_manager.getListaTarefas(idMecanico,idPosto);
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

    public int nextServico(int nif, String matricula) {
        return postos_manager.nextServico(nif,matricula);
    }

    public List<Posto> nextPosto(String matricula) {
        List <Posto> p = postos_manager.getPostos();
        List<Posto> temp = new LinkedList<>();

        for( Posto pt : p){
            List<Servico> l = pt.getTarefas().get(matricula);
            if (l==null){
                continue;
            }
            if (!l.isEmpty()){
                temp.add(pt);
            }
        }
        return temp;
    }
}
