# Código baseado em https://docs.python.org/3.6/library/asyncio-stream.html#tcp-echo-client-using-streams
import asyncio
import os
from cryptography.hazmat.primitives.ciphers.aead import AESGCM
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.kdf.hkdf import HKDF
from cryptography.hazmat.primitives.asymmetric import dh

conn_port = 8443
max_msg_size = 9999
# Valores fixos para p e g
p_value = int("0xFFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7EDEE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3DC2007CB8A163BF0598DA48361C55D39A69163FA8FD24CF5F83655D23DCA3AD961C62F356208552BB9ED529077096966D670C354E4ABC9804F1746C08CA18217C32905E462E36CE3BE39E772C180E86039B2783A2EC07A28FB5C55DF06F4C52C9DE2BCBF6955817183995497CEA956AE515D2261898FA051015728E5A8AACAA68FFFFFFFFFFFFFFFF", 16)
g_value = 2

parameters_numbers = dh.DHParameterNumbers(p_value, g_value)
parameters = parameters_numbers.parameters()

# Gerar chave privada
private_key = parameters.generate_private_key()

# Gerar chave pública
public_key = private_key.public_key()
serialized_public_key = public_key.public_bytes(
    encoding=serialization.Encoding.PEM,
    format=serialization.PublicFormat.SubjectPublicKeyInfo
)

def derive_shared_key(peer_public_key):
    peer_public_key = serialization.load_pem_public_key(peer_public_key)
    shared_key = private_key.exchange(peer_public_key)
    return shared_key

def derive_encryption_key(shared_key):
    # Utilize o HKDF para derivar a chave efetiva para AES-GCM
    hkdf = HKDF(
        algorithm=hashes.SHA256(),
        length=32,  # Tamanho da chave
        salt=None,
        info=b'diffie-hellman-encryption-key',
    )
    encryption_key = hkdf.derive(shared_key)
    return encryption_key

def encode(message, encryption_key):
    nonce = os.urandom(12)

    aesgcm = AESGCM(encryption_key)
    ct = aesgcm.encrypt(nonce, message, None)

    return nonce + ct

def decode(message, encryption_key):
    nonce = message[:12]
    cifra = message[12:]

    aesgcm = AESGCM(encryption_key)
    mensagem = aesgcm.decrypt(nonce, cifra, None)

    return mensagem

class Client:
    """ Classe que implementa a funcionalidade de um CLIENTE. """
    def __init__(self, sckt=None):
        """ Construtor da classe. """
        self.sckt = sckt
        self.msg_cnt = 0
    def process(self, msg=b""):
        
        """ Processa uma mensagem (`bytestring`) enviada pelo SERVIDOR.
            Retorna a mensagem a transmitir como resposta (`None` para
            finalizar ligação) """
        self.msg_cnt +=1
        if self.msg_cnt == 1:
            # Enviar a chave publica ao servidor
            return serialized_public_key
        elif self.msg_cnt == 2:
            # Receber a chave publica do servidor
            peer_public_key = derive_shared_key(msg)
            # Derivar a chave
            self.derive_key = derive_encryption_key(peer_public_key)

        else:
            msg = decode(msg, self.derive_key)
            print('Received (%d): %r' % (self.msg_cnt , msg.decode()))
        print('Input message to send (empty to finish)')
        new_msg = input().encode()
        #
        msg = encode(new_msg, self.derive_key)
        return msg if len(new_msg)>0 else None

#
#
# Funcionalidade Cliente/Servidor
#
# obs: não deverá ser necessário alterar o que se segue
#


async def tcp_echo_client():
    reader, writer = await asyncio.open_connection('127.0.0.1', conn_port)
    addr = writer.get_extra_info('peername')
    client = Client(addr)
    msg = client.process()
    while msg:
        writer.write(msg)
        msg = await reader.read(max_msg_size)
        if msg :
            msg = client.process(msg)
        else:
            break
    writer.write(b'\n')
    print('Socket closed!')
    writer.close()

def run_client():
    loop = asyncio.get_event_loop()
    loop.run_until_complete(tcp_echo_client())


run_client()