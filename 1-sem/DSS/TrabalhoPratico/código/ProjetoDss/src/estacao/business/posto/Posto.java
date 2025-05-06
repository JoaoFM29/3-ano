package estacao.business.posto;

import estacao.business.MecanicoNaoPertenceException;
import estacao.business.Oficina;
import estacao.data.MecanicoDAO;
import estacao.data.ServicoDAO;

import java.time.LocalDateTime;
import java.util.*;

public class Posto {
        private int idPosto;
        private Oficina minha_oficina;
        private int idMecanico;

        private List<Integer> servicos_prestados;

        private Map<String,List<Integer>> tarefas;
        private MecanicoDAO mecanico = MecanicoDAO.getInstance();
        private ServicoDAO acesso_a_servicos = ServicoDAO.getInstance();

        public Posto(int idPosto, int idMecanico){
            this.idPosto = idPosto;
            this.idMecanico = idMecanico;
            this.tarefas = new HashMap<>();
            this.servicos_prestados = new ArrayList<>();
        }

        public int getIdPosto() {
            return idPosto;
        }

        public void setIdPosto(int idPosto) {
            this.idPosto = idPosto;
        }

        public int getIdMecanico() {
            return idMecanico;
        }

        public void setIdMecanico(int idMecanico) {
            this.idMecanico = idMecanico;
        }

        @Override
        public String toString() {
            return "ID do Posto: " + idPosto + ", ID do Mecânico: " + idMecanico + ", Tarefas: " + tarefas + ", Prestados: " + servicos_prestados;
        }

        public void validaMecanico(int idMecanico) throws MecanicoNaoPertenceException {
            if (idMecanico !=this.idMecanico ){
                throw  new MecanicoNaoPertenceException();
            }
        }

        public Map<String,List<Servico>> getTarefas() {
            return acesso_a_servicos.getTarefas(this.idPosto);
        }

    public boolean podeAgendar(Servico sTemp) {
            List<List<Integer>> vls = new ArrayList<>(this.tarefas.values());
            float sum = 0;
            for(List<Integer> l:vls){

                for(Integer s1:l){
                    Servico s = this.acesso_a_servicos.getServico(s1);
                    sum = sum + s.getDuracao();
                }

            }
            LocalDateTime data = LocalDateTime.now();
            sum +=sTemp.getDuracao();
            data.plusMinutes((int) sum);
            LocalDateTime d = minha_oficina.getDataF();
            boolean b = !data.isAfter(d);
            boolean b2 = servicos_prestados.contains(sTemp.getIdServico());
            boolean b3 = b && b2;
            return b3;

    }

    public void agendaServicoPosto(String matricula, Servico sTemp) {
            List<Integer> l = this.tarefas.get(matricula);
            if(l ==null){

                List<Integer> l2 = new ArrayList<>();
                l2.add(sTemp.getIdServico());
                l=l2;


            }else {
                l.add(sTemp.getIdServico());

            }
            this.tarefas.put(matricula,l);
    }

    public void setTarefas(Map<String, List<Integer>> tarefas) {
            this.tarefas = tarefas;
    }

    public void setServicosPrestados(List<Integer> servicosPrestados) {
            this.servicos_prestados = servicosPrestados;
    }

    public  Map<String,List<Integer>> getTarefas2() {
            return this.tarefas;
    }

    public List<Integer> getServicosPrestados() {
            return this.servicos_prestados;
    }

    public void setOficina(Oficina oficina) {
            minha_oficina = oficina;
    }

    public void updateRemServicoVeiculo(String matricula, int idServico) {
            List<Integer> st = this.tarefas.get(matricula);
            st.removeIf(n -> n == idServico);
            if (st.isEmpty()){
                tarefas.remove(matricula);
            }

    }
}


