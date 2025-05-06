import socket
import threading
from datetime import datetime
import time

mapaFicheiros = {}
conectados = {}
lock = threading.Lock()

def fileMapManager():
    while True:
        time.sleep(15)  # Wait for 5 seconds

        current_time = time.time()

        with lock:
            for file_name, clients in list(mapaFicheiros.items()):
                updated_clients = [(address, (seg_info, timestamp)) for address, (seg_info, timestamp) in clients if (current_time - timestamp.timestamp()) <= 60]

                if updated_clients:
                    mapaFicheiros[file_name] = updated_clients
                else:
                    del mapaFicheiros[file_name]

def handle_client(client_socket, client_address):
    while True:
        data = client_socket.recv(1024).decode()
        if not data:
            break

        words = data.split(' ')
        if words[0] == 'regn':
            with lock:
                if client_address not in conectados.keys():
                    conectados[client_address] = (client_socket,words[1])
                    response = "SCS-> Nodo registado"
                elif client_address in conectados.keys() and conectados[client_address] != client_socket:
                    conectados[client_address] = (client_socket,words[1])
                    response = "SCS-> Socket atualizado com sucesso"
                else:
                    response = "ERROR"
            client_socket.send(response.encode())

        elif words[0] == 'regf': # isto acaba por ser automático agora, não sei se vale a pena deixar o cliente mandar files
            with lock:
                if client_address in conectados.keys():
                    try:
                        integer1_seg = int(words[2])
                        integer2_seg = int(words[3])
                        file_name = words[1]

                        if file_name in mapaFicheiros.keys():

                            client_found = False
                            for i, (address, (seg1, seg2)) in enumerate(mapaFicheiros[file_name]):
                                if address == client_address:

                                    mapaFicheiros[file_name][i] = (client_address, ((integer1_seg, integer2_seg),datetime.now()))
                                    client_found = True
                                    break

                            if not client_found:
                                mapaFicheiros[file_name].append((client_address, ((integer1_seg, integer2_seg),datetime.now())))
                        else:
                            mapaFicheiros[file_name] = [(client_address, ((integer1_seg, integer2_seg),datetime.now()))]

                        response = "SCS-> Ficheiro registado com sucesso"

                    except (IndexError, KeyError):
                        response = "ERRO: O campo 'segmento' deve ser um inteiro"
                    client_socket.send(response.encode())
                else:
                    response = "ERRO: Nodo não registado"
                    client_socket.send(response.encode())

        elif words[0] == 'getf':

            with lock:
                if client_address in conectados.keys():
                    try:
                        response = mapaFicheiros[words[1]]
                    except (IndexError):
                        response = "ERRO: Faltam campos na mensagem"
                        client_socket.send(response.encode())
                    except (KeyError):
                        response = "ERRO: Ficheiro não existe"
                        client_socket.send(response.encode())
                else:
                    response = "ERRO: Nodo não registado"

                client_socket.send(str(response).encode())

        else:
            response = "ERRO: Não é instrução"
            client_socket.send(response.encode())
            print(mapaFicheiros)
            print(conectados)

def server_program():
    host = socket.gethostname()
    port = 9090

    print("Host: ",host)

    server_socket = socket.socket()
    server_socket.bind((host, port))
    server_socket.listen(10)


    map_manager = threading.Thread(target=fileMapManager, args=())
    map_manager.start()

    while True:
        client_socket, client_address = server_socket.accept()
        print("Connection from: " + str(client_address))
        client_handler = threading.Thread(target=handle_client, args=(client_socket, client_address))
        client_handler.start()

if __name__ == '__main__':
    server_program()
