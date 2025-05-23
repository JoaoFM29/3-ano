import java.util.*;

class Bank {
    final ReentrantLock l = new ReentrantLock();

    private static class Account {
        final ReentrantLock l = new ReentrantLock();

        private int balance;
        Account(int balance) { this.balance = balance; }
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

    private Map<Integer, Account> map = new HashMap<Integer, Account>();
    private int nextId = 0;
    private ReentrantLock
    private ReentrantReadWriteLock rwl = new ReentrantReadWriteLock();
    private Lock rl = rwl.readLock();
    private Lock wl = rwl.writeLock();
    // create account and return account id
    public int createAccount(int balance) {
        Account c = new Account(balance);
        this.wl.lock();
        try{
            int id = nextId;
            nextId += 1;
            map.put(id, c);
        }finally{
            this.wl.unlock();
        }

        return id;
    }

    // close account and return balance, or 0 if no such account
    public int closeAccount(int id) {
        Account c;
        this.wl.lock();
        try{
            c = map.remove(id);
            if (c == null)
                return 0;
            c.l.lock();
        }finally{
            this.wl.unlock();
        }
        try{
            return c.balance();
        } finally{
            c.l.unlock();
        }
    }

    // account balance; 0 if no such account
    public int balance(int id) {
        Account c;
        this.l.lock();
        try{
            c = map.get(id);
            if (c == null)
               return 0;
            c.l.lock();
        finally{
            this.l.unlock();
        }
        try{
           return c.balance();
        }finally{
            c.l.unlock();
        }
    }

    // deposit; fails if no such account
    public boolean deposit(int id, int value) {
        Account c;
        this.wl.lock();
        try{
            c = map.get(id);
            if (c == null)
                return false;
            c.l.lock();
        finally{
            this.wl.unlock();
        }
        try{
           return c.deposit(value);
        }finally{
            c.l.unlock();
        }
    }

    // withdraw; fails if no such account or insufficient balance
    public boolean withdraw(int id, int value) {
        Account c;
        this.wl.lock();
        try{
            c = map.get(id);
            if (c == null)
               return false;
            c.l.lock();
        }finally{
            this.wl.unlock();
        }
        try{
           return c.withdraw(value);
        }finally{
            c.l.unlock();
        }
    }

    // transfer value between accounts;
    // fails if either account does not exist or insufficient balance
    public boolean transfer(int from, int to, int value) {
        Account cfrom, cto;
        this.rl.lock();
        try{
            cfrom = map.get(from);
            cto = map.get(to);
            if (cfrom == null || cto ==  null)
                return false;
            if(from < to){
                cfrom.l.lock();
                cto.l.lock();
            } else{
                cfrom.l.lock();
                cto.l.lock();
            }
        finally{
            this.rl.unlock();
        }
        try{
            try{
                if(!cfrom.withdraw(value))
                    return false;
            }finally{
                cfrom.l.unlock();
            }
            return cto.deposit(value);
        }finally{
            cto.l.unlock();
        }
    }

    // sum of balances in set of accounts; 0 if some does not exist
    public int totalBalance(int[] ids) {
        ids = ids.clone();
        Arrays.sort(ids);
        Account aux = new Account[ids.length];
        this.l.lock();
        try{
            for(int i = 0; i < ids.length; i++){
               aux[i] = map.get(ids[i]);
               if (aux[i] == null) return 0;
            }
            for(Account c : aux)
                c.l.unlock();
        }finally{
            this.l.unlock();
        }

        int total = 0;
        for (Account c : aux) {
           total += c.balance();
           c.unlock();
        }
        return total;
    }