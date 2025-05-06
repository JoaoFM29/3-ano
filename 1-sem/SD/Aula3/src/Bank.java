import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
public class Bank {

    Lock l = new ReentrantLock();

    private static class Account {

        private int balance;
        Account(int balance) {this.balance = balance; }

        int balance() { return balance; }
        boolean deposit(int value) {
            balance += value;
            return true;
        }
        boolean withdraw(int value) {
            if (value > balance)
                return false;
            balance -= value;
            return true;
        }
    }

    // Bank slots and vector of accounts
    private int slots;
    private Account[] av;

    public Bank(int n) {
        slots=n;
        av=new Account[slots];
        for (int i=0; i<slots; i++) av[i]=new Account(0);
    }

    // Account balance
    public int balance(int id) {
        if (id < 0 || id >= slots)
            return 0;
        try{
            this.l.lock();
            return av[id].balance();
        }finally {
            l.unlock();
        }
    }

    // Deposit
    public boolean deposit(int id, int value) {
        if (id < 0 || id >= slots)
            return false;
        try{
            this.l.lock();
            return av[id].deposit(value);
        }finally {
            l.unlock();
        }
    }

    // Withdraw; fails if no such account or insufficient balance
    public boolean withdraw(int id, int value) {
        if (id < 0 || id >= slots)
            return false;
        try{
            l.lock();
            return av[id].withdraw(value);
        }finally {
            l.unlock();
        }
    }
    boolean transfer (int from, int to, int value){
        if (from < 0 || from >= slots || to < 0 || to >= slots)
            return false;
        try{
            l.lock();
            this.withdraw(from,value);
            this.deposit(from,value);
            return true;
        }finally {
            l.unlock();
        }
    }

    int totalBalance(){
        int soma = 0;
        for(int i = 0; i<slots; i++) {
            soma += this.balance(i);
        }
        return soma;
    }
}
