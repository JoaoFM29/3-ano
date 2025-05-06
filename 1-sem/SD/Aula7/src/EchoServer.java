
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.locks.ReentrantLock;

/*
public class EchoServer {

    public static void main(String[] args) {
        try {
            ServerSocket ss = new ServerSocket(12345);

            while (true) {
                Socket socket = ss.accept();

                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter out = new PrintWriter(socket.getOutputStream());

                String line;
                int soma = 0;
                int quant = 0;
                double media = 0.0;
                while ((line = in.readLine()) != null) {
                    soma += Integer.parseInt(line);
                    quant++;
                    line = Integer.toString(soma);
                    out.println(line);
                    out.flush();
                }

                media = soma/quant;
                line = Double.toString(media);
                out.println(line);
                out.flush();

                socket.shutdownOutput();
                socket.shutdownInput();
                socket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
*/

class Register{
    private ReentrantLock l = new ReentrantLock();
    int soma = 0;
    int count = 0;

    public void add(int value){
        l.lock();
        try {
            soma += value;
            count++;
        }finally {
            l.unlock();
        }

    }

    public double average(){
        l.lock();
        try{
            return soma/count;
        }finally {
            l.unlock();
        }
    }
}

class ClientHandler extends Thread {
    Socket socket;
    Register r;
    ClientHandler(Socket socket, Register r) {
        this.socket = socket;
        this.r = r;
    }

    public void run(){
        try{
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream());

            String line;
            int soma = 0;

            while ((line = in.readLine()) != null) {
                int value = Integer.parseInt(line);
                soma += value;
                r.add(value);
                line = Integer.toString(soma);
                out.println(line);
                out.flush();
            }

            double media = r.average();
            line = Double.toString(media);
            out.println(line);
            out.flush();

            socket.shutdownOutput();
            socket.shutdownInput();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

public class EchoServer {

    public static void main(String[] args) {
        try {
            ServerSocket ss = new ServerSocket(12345);
            Register r = new Register();
            while (true) {
                Socket socket = ss.accept();
                new ClientHandler(socket, r).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}