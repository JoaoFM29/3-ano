package estacao.business.posto;

import estacao.business.MecanicoNaoPertenceException;
import estacao.business.NaoTemDisponibilidadeException;
import estacao.business.Oficina;
import estacao.business.VeiculoNaoPodeException;
import estacao.data.ClienteDAO;
import estacao.data.PostoDAO;
import estacao.data.ServicoDAO;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class SubFuncPostosFacade implements ISubFuncPostos {
    private final ClienteDAO clientes;
    private final PostoDAO postos;
    private final ServicoDAO servicos;
    private Oficina oficina;
    public SubFuncPostosFacade(Oficina ofi) {
        this.clientes = ClienteDAO.getInstance();
        this.servicos = ServicoDAO.getInstance();
        this.postos = PostoDAO.getInstance();
        this.oficina = ofi;
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

    private List<Servico> buscarServicos(int idServico){
        List<Servico> res = new ArrayList<>();
        boolean b = servicos.isPack(idServico);
        if (!b){
            Servico s = servicos.getServico(idServico);
            res.add(s);
        }else{

            PackServico lps = servicos.getPack(idServico);
            res.addAll(lps.getSv());
        }

        return res;
    }
    @Override
    public void atualizaFichaVeiculoNovaIntervencao(String matricula, int idServico, int nif) throws VeiculoNaoPodeException {
       List<Servico> s = buscarServicos(idServico);
       Cliente c = clientes.getCliente(nif);
       c.updateVeiculo(matricula,s);
       clientes.updateCliente(c);
    }

    @Override
    public List<Posto> getPostos() {
        return postos.getPostos();
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
    public Posto agendarServico(String matricula, int idServ) throws NaoTemDisponibilidadeException {
       List<Posto> psts = getPostos();
       List<Servico> servics = buscarServicos(idServ);

       List<Integer> ids = servics.stream().map(Servico::getIdServico).toList();
       Posto pl = null;
       for(Integer idServico : ids){
           boolean b1 = false;
           Servico s_temp = servicos.getServico(idServico);
           for(Posto p : psts){
               if (b1) break;
               p.setOficina(oficina);
               b1 = p.podeAgendar(s_temp);



               if(b1) {
                   pl = p;
                   p.agendaServicoPosto(matricula, s_temp);

               }

           }
           if(!b1){
               throw new NaoTemDisponibilidadeException();

           }
           postos.updatePosto(pl);


       }
        return pl;



    }


    @Override
    public boolean atualizaFichaVeiculoConcluido(String matricula, int idServico, int nif,int idPosto) { // atualizar

        Cliente c = clientes.getCliente(nif);
        boolean b = c.updateRemVeiculo(matricula,idServico);
        Posto p = postos.getPosto(idPosto);
        p.updateRemServicoVeiculo(matricula,idServico);
        clientes.updateCliente(c);
        postos.updatePosto(p);
        return b;

    }

    @Override
    public void atualizaFichaVeiculoCheckUp(String matricula, List<Integer> idServico, int nif) throws VeiculoNaoPodeException{
        List<Servico> s = new ArrayList<>();
        for (Integer id:idServico){
            List<Servico> sTemp = buscarServicos(id);
            s.addAll(sTemp);
        }
        Cliente c = clientes.getCliente(nif);
        c.updateVeiculo(matricula,s);
        clientes.updateCliente(c);

    }

    @Override
    public boolean avisarCliente(int nif) {
        Cliente c = clientes.getCliente(nif);
        int cont = c.getContacto();
        //Enviar uma mensagem!
        boolean b = true;
        return b;
    }

    @Override
    public Map<String,List<Servico>> getListaTarefas(int idMecanico, int idPosto) throws MecanicoNaoPertenceException {
        Posto p = postos.getPosto(idPosto);
        p.setOficina(oficina);
        p.validaMecanico(idMecanico);
        Map<String,List<Servico>> mp = p.getTarefas();
        return mp;
    }

    public int nextServico(int nif, String matricula) {
        Cliente c = this.clientes.getCliente(nif);
        Veiculo V = null;
        for (Veiculo v: c.getVeiculos()){

            if (v.getMatricula().equals(matricula)){
                V = v;
                break;
            }
        }
        return V.getFichaVeiculo().get(0);
    }
}
