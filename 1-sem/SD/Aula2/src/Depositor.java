public class Depositor implements Runnable  {
    Bank B;
    final int D;
    final int V;
    Depositor(int D2,int V2, Bank B) {
        this.D = D2;
        this.V = V2;
        this.B = B;
    }
    public void run() {
        for (long i = 0; i < D; i++)
            B.deposit(V);
    }
}
