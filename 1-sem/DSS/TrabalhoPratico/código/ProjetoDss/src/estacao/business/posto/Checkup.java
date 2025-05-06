package estacao.business.posto;

import estacao.business.posto.Servico;

public class Checkup extends Servico {
    public Checkup(int idServico, String designacao, float duracao, float preco) {
        super(idServico, designacao, duracao, preco);
    }
}