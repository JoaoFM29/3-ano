public class D implements Runnable{
    @Override
    public void run(){
        for(long  l = 0; l< 1L << 32; l++);
        System.out.println("Na Thread");
    }
}
