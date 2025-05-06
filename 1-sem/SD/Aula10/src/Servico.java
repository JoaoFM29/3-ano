import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

interface Jogo {
    Partida inscrever() throws InterruptedException;
    void começar();
}

interface Partida {
    int participantes();
    boolean aposta(int parcela, int estimativa) throws InterruptedException;
}

class JogoImp implements Jogo{
    ReentrantLock l = new ReentrantLock();
    Condition cond = l.newCondition();
    PartidaImp partida = new PartidaImp();
    public Partida inscrever() throws InterruptedException {
        l.lock();
        try{
            PartidaImp p = partida;
            p.participantes ++;
            while(!p.comecou){
                cond.await();
            }
            return p;
        } finally {
            l.unlock();
        }
    }
    public void começar(){
        l.lock();
        try{
            partida.comecou = true;
            cond.signalAll();
            partida = new PartidaImp();
        }finally {
            l.unlock();
        }
    }
}
class PartidaImp implements Partida{
    boolean comecou = false;
    int participantes = 0;
    List<Integer> apostas = new ArrayList<>();
    ReentrantLock l = new ReentrantLock();
    Condition cond = l.newCondition();

    public int participantes (){
    }
    public boolean aposta(int parcela, int estimativa) throws InterruptedException {

    }
}
