import socket
import sys
import threading
import os
import time
import subprocess




MyFiles = {} #mapa de ficheiros nome do ficheiro para

def set_reciever():
    return


def checker(folder, socket):
    while True:
        try:
            files = os.listdir(folder)
            for file in files:
                file_path = os.path.join(folder, file)
                if os.path.isfile(file_path):
                    file_name = os.path.basename(file_path)
                    file_size = os.path.getsize(file_path)
                    MyFiles[file_name] = (file_size, file_path)  # Update MyFiles dictionary

                    # Send the information to the socket
                    message = f"regf {file_name} 1 {file_size}"
                    socket.send(message.encode())
                    socket.recv(1024).decode()

        except Exception as e:
            print(f"Error while checking folder: {str(e)}")

        # Sleep for 30 seconds
        time.sleep(30)


def client_program(folder,host):


    port = 9090  # porta usada em tcp
    # UDP configuration
    try:
        udp_port = 8080  # Choose a suitable UDP port
        udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        udp_socket.bind(("0.0.0.0", udp_port))
    except:
        print("ERROR: Erro no bind da socket udp")

    try:
        client_socket = socket.socket()
        client_socket.connect((host, port))
        print("SCS:Conectado a ",host)

    except:
        print("ERROR: Host não existe")
        return




    #registar nodo assim que se conecta
    message = "regn " + str(udp_socket)
    client_socket.send(message.encode())
    client_socket.recv(1024).decode()

    #criar thread de check na pasta de ficheiros
    ct = threading.Thread(target=checker, args=(folder,client_socket))
    ct.start()

    # inciar daemon para cliente interagir com o server
    message = input(" -> ")
    while message.lower().strip() != 'quit':
        aux = message.split()
        client_socket.send(message.encode())
        data = client_socket.recv(1024).decode()
        print('Resposta do servidor: ' + data)
        if (aux[0] == "getf"):
            set_reciever()

        message = input(" -> ")

    client_socket.close()



if __name__ == '__main__':
    if len(sys.argv) > 1:
        arg1 = sys.argv[1]
        arg2 = sys.argv[2]
    else:
        print("Please provide arguments.")
        sys.exit(1)

    # Function to run client_program in a thread
    def run_client_program():
        client_program(arg1, arg2)

    # Function to run C++ program in a thread
    def run_cpp_program():
        # Replace 'path_to_your_cpp_program' with the actual path to your C++ program
        subprocess.run(['fs_transfer_protocol/./sender'])

    # Create threads for client_program and C++ program execution
    client_thread = threading.Thread(target=run_client_program)
    cpp_thread = threading.Thread(target=run_cpp_program)

    # Start both threads
    client_thread.start()
    cpp_thread.start()

    # Wait for both threads to finish
    client_thread.join()
    cpp_thread.join()