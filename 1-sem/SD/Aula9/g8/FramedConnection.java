package g8;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class FramedConnection implements AutoCloseable {
        private Socket socket;
        private DataOutputStream out;
        private DataInputStream in;
        private ReentrantLock li = new ReentrantLock() ;
        private ReentrantLock lo = new ReentrantLock() ;

    public FramedConnection(Socket socket) throws IOException {
        this.socket = socket;
        this.out = new DataOutputStream(this.socket.getOutputStream());
        this.in = new DataInputStream(this.socket.getInputStream());
    }

    public void send(byte[] data) throws IOException {
        lo.lock();
        try{
            this.out.write(data.length);
            this.out.write(data);
        }finally {
            lo.unlock();
        }
    }
    public byte[] receive() throws IOException {
        li.lock();
        try{
            return this.in.readNBytes(this.in.readInt());
        }finally {
            li.unlock();
        }
    }
    public void close() throws IOException {
        socket.close();
    }
}
