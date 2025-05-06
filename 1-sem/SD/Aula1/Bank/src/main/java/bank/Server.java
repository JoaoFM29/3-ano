package bank;

import io.grpc.Grpc;
import io.grpc.InsecureServerCredentials;
import io.grpc.stub.StreamObserver;

import java.util.concurrent.Executors;

// executar com: mvn exec:java -Dexec.mainClass="bank.Server"
public class Server extends BankGrpc.BankImplBase {
    @Override
    public void bank(BankRequest request, StreamObserver<BankReply> responseObserver) {
        responseObserver.onNext(
                BankReply.newBuilder().setGreeting(
                        "Bank "+request.getWho()+"!"
                ).build());
        responseObserver.onCompleted();
    }

    public static void main(String[] args) throws Exception {
        Grpc.newServerBuilderForPort(12345, InsecureServerCredentials.create())
                .addService(new Server())
                .executor(Executors.newSingleThreadExecutor())
                .build().start().awaitTermination();
    }
}
