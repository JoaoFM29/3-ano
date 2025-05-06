import java.util.*;


class Barrier {
    private ReentrantLock l = new ReentrantLock();
    private Condition cond = l.newCondition();
    private int count = 0;
    private int countE = 0;
    private final int N;

    Barrier (int N) {
        this.N = N;
    }

    void await() throws InterruptedException {
        l.lock();
        try{
            int E = this.countE;
            this.count += 1;
            if (count == N)
                cond.signalAll();
                this.count = 0;
                this.countE += 1;
            else while(E == this.countE) // --> enquanto forem iguais, significa que ainda não chegou à N-ésima
                cond.await();
        }finally{
            l.unlock();
        }
    }

    void await2() throws InterruptedException {
        l.lock();
        try{
            count += 1;
            while(count < N)
                cond.await();
            cond.signal();
        }finally{
            l.unlock();
        }
    }
}