class Increment implements Runnable {
    final long I;
    Increment(long I2) {this.I = I2;}

    public void run() {
        for (long i = 0; i < I; i++)
            System.out.println(i);
    }
}