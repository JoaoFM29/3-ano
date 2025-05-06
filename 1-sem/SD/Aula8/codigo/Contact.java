import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.*;

class Contact {
    private final String name;
    private final int age;
    private final long phoneNumber;
    private final String company;     // Pode ser null
    private final ArrayList<String> emails;

    public Contact(String name, int age, long phoneNumber, String company, List<String> emails) {
        this.name = name;
        this.age = age;
        this.phoneNumber = phoneNumber;
        this.company = company;
        this.emails = new ArrayList<>(emails);
    }

    public String name() { return name; }
    public int age() { return age; }
    public long phoneNumber() { return phoneNumber; }
    public String company() { return company; }
    public List<String> emails() { return new ArrayList<>(emails); }

    // @TODO
    public void serialize(DataOutputStream out) throws IOException {
        out.writeUTF(name());
        out.writeInt(age());
        out.writeLong(phoneNumber());
        boolean companyNotNull = company != null;
        if(companyNotNull)
            out.writeBoolean(true);
        out.writeInt(emails.size());
        for(String s : emails) {
            out.writeUTF(s);
        }
    }

    // @TODO
    public static Contact deserialize(DataInputStream in) throws IOException {
        String name = in.readUTF();
        int age = in.readInt();
        long phoneNumber = in.readLong();
        boolean b = in.readBoolean();
        String company = null;
        if(b == true){
            company = in.readUTF();
        }
        int aux = in.readInt();
        List<String> emailsAux = new ArrayList<>();
        for(int i = 0; i<aux; i++){
            emailsAux.add(in.readUTF());
        }
        return new Contact(name,age,phoneNumber,company,emailsAux);
    }

    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append(this.name).append(";");
        builder.append(this.age).append(";");
        builder.append(this.phoneNumber).append(";");
        builder.append(this.company).append(";");
        builder.append(this.emails.toString());
        builder.append("}");
        return builder.toString();
    }

}
