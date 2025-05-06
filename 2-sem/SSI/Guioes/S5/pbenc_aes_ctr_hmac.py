import sys
import struct, os
import cryptography
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import hashes, hmac
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC


#Neste exercício, encriptamos uma mensagem e enviamos a mensagem encripatada e enviamos para o ficheiro juntamente com o HMAC criado com a chave.
#Depois ao ler do ficheiro, lemos a mensagem encriptada, desincriptamos e fazemos o hmac dessa mensagem e compramos com o hmac que enviamos em cima a ver se sao iguais.

def derive(password, salt):
    kdf = PBKDF2HMAC(
        algorithm=hashes.SHA256(),
        length=64,
        salt=salt,
        iterations=480000,
    ) 
    return kdf.derive(password)
 
    
def encode(in_file,chave_texto):
    with open(in_file, 'rb') as in_file_read:
        mensagem = in_file_read.read()
    
    salt = os.urandom(16)
    nonce = os.urandom(16) 
    
    chave = derive(chave_texto.encode(), salt)
    key = chave[:32]
    key2 = chave[32:]

    algorithm = algorithms.AES(key)
    cipher = Cipher(algorithm,modes.CTR(nonce))
    encryptor = cipher.encryptor()
    ct = encryptor.update(mensagem)
    
    h = hmac.HMAC(key2, hashes.SHA256())
    h.update(ct)
    signature = h.finalize()
    
    with open(in_file + ".enc", 'wb') as out_f:
        out_f.write(nonce)
        out_f.write(salt)
        out_f.write(signature)
        out_f.write(ct)
    pass

def decode(in_file, chave_texto):
    with open(in_file, 'rb') as in_file_read:
        nonce = in_file_read.read(16)
        salt = in_file_read.read(16)
        signature = in_file_read.read(32)
        cifra = in_file_read.read()

    chave = derive(chave_texto.encode(), salt)
    key = chave[:32]
    key2 = chave[32:]

    algorithm = algorithms.AES(key)
    cipher = Cipher(algorithm, modes.CTR(nonce))
    decryptor = cipher.decryptor()
    mensagem = decryptor.update(cifra)

    h = hmac.HMAC(key2, hashes.SHA256())
    h.update(cifra)

    try:
        h.verify(signature)
        with open(in_file + ".dec", 'wb') as out_f:
            out_f.write(mensagem)   
    except cryptography.exceptions.InvalidSignature:
        print("Erro: Assinatura inválida. A verificação falhou.")


def main(inp):
    if (len(inp) < 3):
        print("Sem argumentos suficientes")
    else:
        if(inp[1]=='enc'):
            encode(inp[2],inp[3])
        if(inp[1]=='dec'):
            decode(inp[2],inp[3])
            
# Se for chamada como script...
if __name__ == "__main__":
    main(sys.argv)