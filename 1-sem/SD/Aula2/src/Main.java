// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) throws InterruptedException {
        int N = Integer.parseInt(args[0]);
        int D = Integer.parseInt(args[1]);
        int V = Integer.parseInt(args[2]);

        Bank conta = new Bank();
        Thread[] a = new Thread[N];

        for(int i = 0; i < N; i++){
            a[i] = new Thread(new Depositor(D,V,conta));
        }

        for(int i = 0; i < N; i++){
            a[i].start();
        }

        for(int i = 0; i < N; i++){
            a[i].join();
        }

        System.out.println(conta.balance());
    }
}