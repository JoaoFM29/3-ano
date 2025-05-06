import sys
import os
from cryptography.hazmat.primitives.ciphers.aead import AESGCM
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC

def derive(password, salt):
    kdf = PBKDF2HMAC(
        algorithm=hashes.SHA256(),
        length=32,
        salt=salt,
        iterations=480000,
    )
    return kdf.derive(password)

def encode(in_file, chave_texto):
    with open(in_file, 'rb') as in_file_read:
        mensagem = in_file_read.read()

    salt = os.urandom(16)
    nonce = os.urandom(12)

    chave = derive(chave_texto.encode(), salt)
    aesgcm = AESGCM(chave)
    ct = aesgcm.encrypt(nonce, mensagem, None)

    with open(in_file + ".enc", 'wb') as out_f:
        out_f.write(nonce)
        out_f.write(salt)
        out_f.write(ct)

def decode(in_file, chave_texto):
    with open(in_file, 'rb') as in_file_read:
        nonce = in_file_read.read(12)
        salt = in_file_read.read(16)
        cifra = in_file_read.read()

    chave = derive(chave_texto.encode(), salt)

    aesgcm = AESGCM(chave)
    mensagem = aesgcm.decrypt(nonce, cifra, None)

    with open(in_file + ".dec", 'wb') as out_f:
        out_f.write(mensagem)

def main(inp):
    if (len(inp) < 3):
        print("Sem argumentos suficientes")
    else:
        if(inp[1]=='enc'):
            encode(inp[2], inp[3])
        if(inp[1]=='dec'):
            decode(inp[2], inp[3])

# Se for chamada como script...
if __name__ == "__main__":
    main(sys.argv)
