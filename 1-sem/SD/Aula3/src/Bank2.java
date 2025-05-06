import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
public class Bank2 {

    private static class Account {

        final ReentrantLock l = new ReentrantLock();

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

    public Bank2(int n) {
        slots=n;
        av=new Account[slots];
        for (int i=0; i<slots; i++) av[i]=new Account(0);
    }

    // Account balance
    public int balance(int id) {
        if (id < 0 || id >= slots)
            return 0;
        Account a = av[id];
        a.l.lock();
        try{
            return av[id].balance();
        }finally {
            a.l.unlock();
        }
    }

    // Deposit
    public boolean deposit(int id, int value) {
        if (id < 0 || id >= slots)
            return false;
        Account a = av[id];
        a.l.lock();
        try{
            return av[id].deposit(value);
        }finally {
            a.l.unlock();
        }
    }

    // Withdraw; fails if no such account or insufficient balance
    public boolean withdraw(int id, int value) {
        if (id < 0 || id >= slots)
            return false;
        Account a = av[id];
        a.l.lock();
        try{
            return av[id].withdraw(value);
        }finally {
            a.l.unlock();
        }
    }
    boolean transfer (int from, int to, int value){
        if (from < 0 || from >= slots || to < 0 || to >= slots)
            return false;
        Account a = av[to];
        Account a2 = av[from];

        if(from < to){
            a.l.lock();
            a2.l.lock();
        }
        else{
            a2.l.lock();
            a.l.lock();
        }
        try{
            try{
                if(!withdraw(from, value))
                    return false;
            }finally{
               a2.l.unlock();
            }
        return this.deposit(to,value);
        }finally {
           a.l.unlock();
        }
    }

    public int totalBalance(){
        int soma = 0;
        for(int i = 0; i < slots; i++)
            av[i].l.lock();
        for(int i = 0; i < slots; i++){
            soma += av[i].balance();
            av[i].l.unlock();
        }
        return soma;
    }
}

