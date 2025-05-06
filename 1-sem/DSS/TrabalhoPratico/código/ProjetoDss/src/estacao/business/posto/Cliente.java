package estacao.business.posto;

import estacao.business.VeiculoNaoPodeException;

import java.util.*;

public class Cliente {

    private String nome;

    private int contacto;

    private String email;

    private int nif;

    private String morada;

    private Voucher voucher;

    private Map<String, Veiculo> veiculos;

    public Cliente(String nome, int contacto, String email, int nif, String morada) {
        this.nome = nome;
        this.contacto = contacto;
        this.email = email;
        this.nif = nif;
        this.morada = morada;
        this.veiculos = new HashMap<>();
    }
    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public int getContacto() {
        return contacto;
    }

    public void setContacto(int contacto) {
        this.contacto = contacto;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public int getNif() {
        return nif;
    }

    public void setNif(int nif) {
        this.nif = nif;
    }

    public void addVeiculo(Veiculo v){
        this.veiculos.put(v.getMatricula(),v);
    }
    public String getMorada() {
        return morada;
    }

    public void setMorada(String morada) {
        this.morada = morada;
    }

    public Voucher getVoucher() {
        return voucher;
    }

    public void setVoucher(Voucher voucher) {
        this.voucher = voucher;
    }

    @Override
    public String toString() {
        return "estacao.business.posto.Cliente{" +
                "nome='" + nome + '\'' +
                ", contacto=" + contacto +
                ", email='" + email + '\'' +
                ", nif=" + nif +
                ", morada='" + morada + '\'' +
                ", voucher=" + voucher +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Cliente cliente = (Cliente) o;
        return contacto == cliente.contacto && nif == cliente.nif && Objects.equals(nome, cliente.nome) && Objects.equals(email, cliente.email) && Objects.equals(morada, cliente.morada) && Objects.equals(voucher, cliente.voucher);
    }

    public void updateVeiculo(String mat,List<Servico> s) throws VeiculoNaoPodeException{
        Veiculo v = this.veiculos.get(mat);
        List<Motor> lm = v.getMotor();
        boolean cant = true;
        for (Servico teste : s){
            if (!cant) break;

            if (teste instanceof ServicoGasoleo){
                boolean hasOne = false;
                for (Motor m : lm){

                    if (m instanceof MotorGasoleo){
                        hasOne = true;
                    }
                }
                cant = hasOne;
            } else if (teste instanceof ServicoGasolina) {
                boolean hasOne = false;
                for (Motor m : lm){

                    if (m instanceof MotorGasolina){
                        hasOne = true;
                    }
                }
                cant = hasOne;
            }else if (teste instanceof ServicoEletrico) {
                boolean hasOne = false;
                for (Motor m : lm){

                    if (m instanceof MotorEletrico){
                        hasOne = true;
                    }
                }
                cant = hasOne;
            }else if (teste instanceof ServicoCombustao) {
                boolean hasOne = false;
                for (Motor m : lm){

                    if (m instanceof MotorCombustao){
                        hasOne = true;
                    }
                }
                cant = hasOne;
            }
        }
        if (!cant){
            throw new VeiculoNaoPodeException();
        }
        List <Integer> l = v.getFichaVeiculo();
        for(Servico serv : s){
            l.add(serv.getIdServico());

        }
    }

    public List<Veiculo> getVeiculos() {
        return new ArrayList<Veiculo>(this.veiculos.values());
    }
    public boolean updateRemVeiculo(String mat,int idServ){
        Veiculo v = veiculos.get(mat);
        List<Integer> l = v.getFichaVeiculo();
        l.removeIf(n -> n == idServ);
        boolean b = l.isEmpty();
        return b;
    }
}
