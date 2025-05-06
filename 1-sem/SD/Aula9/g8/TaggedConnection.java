package g8;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.concurrent.locks.ReentrantLock;

public class TaggedConnection implements AutoCloseable {
    private Socket socket;
    private DataOutputStream out;
    private DataInputStream in;
    private ReentrantLock li = new ReentrantLock() ;
    private ReentrantLock lo = new ReentrantLock() ;

    public static class Frame {
        public final int tag;
        public final byte[] data;
        public Frame(int tag, byte[] data) {
            this.tag = tag;
            this.data = data;
        }
    }

    public TaggedConnection(Socket socket) throws IOException {
        this.socket = socket;
        this.out = new DataOutputStream(this.socket.getOutputStream());
        this.in = new DataInputStream(this.socket.getInputStream());

    }
    public void send(Frame frame) throws IOException {
        lo.lock();
        try{
            send(frame.tag, frame.data);
        }finally {
            lo.unlock();
        }
    }

    public void send(int tag, byte[] data) throws IOException {
        lo.lock();
        try{
            this.out.writeInt(data.length + 4);
            this.out.writeInt(tag);
            this.out.write(data);
            this.out.flush();
        }finally {
            lo.unlock();
        }
    }

    public Frame receive() throws IOException {
        li.lock();
        try{
            int len = in.readInt();
            int tag = in.readInt();
            byte[] data = new byte[len-4];
            in.readFully(data);
            return new Frame(tag,data);
        }finally {
            li.unlock();
        }
    }

    public void close() throws IOException {
        this.socket.close();
    }
}
