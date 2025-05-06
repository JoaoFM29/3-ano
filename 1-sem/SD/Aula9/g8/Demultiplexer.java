package g8;

import java.awt.*;
import java.io.IOException;
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Demultiplexer implements AutoCloseable {
    ReentrantLock l = new ReentrantLock();
    private class Entry{
        Condition cond = l.newCondition();
        Deque<byte[]> deque = new ArrayDeque<>(){
        };
        int waiters = 0;
    };
    Map<Integer, Entry> map = new HashMap<>();
    TaggedConnection conn;

    public Demultiplexer(TaggedConnection conn) {
        this.conn = conn;
    }
    private Entry get(int tag){
        Entry e = map.get(tag);
        if(e==null){
            e = new Entry();
            map.put(tag, e);
        }
        return e;
    }
    public void start() {
        new Thread(()->{
            for(;;){
                Frame f = conn.receive();
                l.lock();
                try{
                    Entry e = get(f.tag);
                    e.deque.add(f.data);
                    e.cond.signal();
                }finally {
                    l.unlock();
                }
            }
        }).start();
    }
    public void send(Frame frame) throws IOException {
         conn.send(frame);
    }
    public void send(int tag, byte[] data) throws IOException {
        conn.send(tag, data);
    }
    public byte[] receive(int tag) throws IOException, InterruptedException {
        l.lock();
        try{
            Entry e = get(tag);
            while(e.deque.isEmpty()){
                e.cond.await();
            }
        }finally {
            l.unlock();
        }
    }
    public void close() throws IOException {

    }
}