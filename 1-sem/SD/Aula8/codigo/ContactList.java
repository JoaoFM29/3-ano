import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.concurrent.locks.ReentrantLock;

class ContactList extends ArrayList<Contact> {
    private ReentrantLock l = new ReentrantLock();
    // @TODO
    public void serialize(DataOutputStream out) throws IOException {
        out.writeInt(this.size());
        l.lock();
        try{
            for(int i = 0; i<this.size(); i++){
                Contact aux = get(i);
                aux.serialize(out);
            }
        }finally {l.unlock();}
    }

    // @TODO
    public static ContactList deserialize(DataInputStream in) throws IOException {
       ContactList aux = new ContactList();
       int count = in.readInt();
        for(int i = 0; i<count; i++){
            Contact c = Contact.deserialize(in);
            aux.add(c);
        }
        return aux;
    }
}
