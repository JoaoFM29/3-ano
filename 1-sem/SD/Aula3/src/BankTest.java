import java.util.Random;

public class BankTest {

    private static class Mover implements Runnable {
        Bank2 b;
        int s; // Number of accounts

        public Mover(Bank2 b, int s) { this.b=b; this.s=s; }

        public void run() {
            final int moves=100000;
            int from, to;
            Random rand = new Random();

            for (int m=0; m<moves; m++) {
                from=rand.nextInt(s); // Get one
                while ((to=rand.nextInt(s))==from); // Slow way to get distinct
                b.transfer(from,to,1);
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        final int N=10;

        Bank2 b = new Bank2(N);

        for (int i=0; i<N; i++)
            b.deposit(i,1000);

        System.out.println(b.totalBalance());

        Thread t1 = new Thread(new Mover(b,10));
        Thread t2 = new Thread(new Mover(b,10));

        t1.start(); t2.start(); t1.join(); t2.join();

        System.out.println(b.totalBalance());
    }
}