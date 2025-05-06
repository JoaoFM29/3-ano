import sys
import struct, os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC


counter = 0    
    
def encode(in_file,chave_texto):
    global counter
    with open(in_file, 'rb') as in_file_read:
        mensagem = in_file_read.read()
    
    salt = os.urandom(16)
    # derive
    kdf = PBKDF2HMAC(
        algorithm=hashes.SHA256(),
        length=32,
        salt=salt,
        iterations=480000,
    )
    chave = kdf.derive(chave_texto.encode())
    # verify
    kdf = PBKDF2HMAC(
        algorithm=hashes.SHA256(),
        length=32,
        salt=salt,
        iterations=480000,
    )
    kdf.verify(chave_texto.encode(), chave)
    nonce = os.urandom(16) 
    counter += 1
    algorithm = algorithms.ChaCha20(chave, nonce)
    cipher = Cipher(algorithm, mode=None)
    encryptor = cipher.encryptor()
    ct = encryptor.update(mensagem)
    with open(in_file + ".enc", 'wb') as out_f:
        out_f.write(nonce)
        out_f.write(salt)
        out_f.write(ct)
    pass

def decode(in_file,chave_texto):
    global counter
    
    with open(in_file, 'rb') as in_file_read:
        nonce = in_file_read.read(16)
        salt = in_file_read.read(16)
        cifra = in_file_read.read()
    
    kdf = PBKDF2HMAC(
        algorithm=hashes.SHA256(),
        length=32,
        salt=salt,
        iterations=480000,
    )
    chave = kdf.derive(chave_texto.encode())
    kdf = PBKDF2HMAC(
        algorithm=hashes.SHA256(),
        length=32,
        salt=salt,
        iterations=480000,
    )
    kdf.verify(chave_texto.encode(), chave)
    counter += 1
    algorithm = algorithms.ChaCha20(chave, nonce)
    cipher = Cipher(algorithm, mode=None)
    decryptor = cipher.decryptor()
    mensagem = decryptor.update(cifra)
    
    with open(in_file + ".dec", 'wb') as out_f:
        out_f.write(mensagem)   
    pass

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