import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.concurrent.locks.ReentrantLock;

import static java.util.Arrays.asList;

class ContactManager {
    private ReentrantLock l = new ReentrantLock();
    private HashMap<String, Contact> contacts = new HashMap<>();

    // @TODO
    public void update(Contact c) {
        l.lock();
        try{
            contacts.put(c.name(), c);
        }finally {l.unlock();}
    }

    // @TODO
    public ContactList getContacts() {
        l.lock();
        ContactList aux = null;
        try{
            for(Contact c: contacts.values()){
                aux.add(c);
            }
        }finally {l.unlock();}
        return aux;
    }
}

class ServerWorker implements Runnable {
    private Socket socket;
    private ContactManager manager;

    public ServerWorker(Socket socket, ContactManager manager) {
        this.socket = socket;
        this.manager = manager;
    }

    // @TODO
    @Override
    public void run(){
        try{
            DataInputStream in = new DataInputStream(this.socket.getInputStream());
            PrintWriter out = new PrintWriter(socket.getOutputStream());

            try {
                while(true) {
                    Contact aux = Contact.deserialize(in);
                    this.manager.update(aux);
                    out.println(this.manager);
                    out.flush();
                }
            }catch (IOException e){
                socket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}


public class Server {

    public static void main (String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(12345);
        ContactManager manager = new ContactManager();
        // example pre-population
        manager.update(new Contact("John", 20, 253123321, null, asList("john@mail.com")));
        manager.update(new Contact("Alice", 30, 253987654, "CompanyInc.", asList("alice.personal@mail.com", "alice.business@mail.com")));
        manager.update(new Contact("Bob", 40, 253123456, "Comp.Ld", asList("bob@mail.com", "bob.work@mail.com")));

        while (true) {
            Socket socket = serverSocket.accept();
            Thread worker = new Thread(new ServerWorker(socket, manager));
            worker.start();
        }
    }

}
