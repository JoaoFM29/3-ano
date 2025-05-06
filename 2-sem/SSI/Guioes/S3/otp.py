import sys
import os

def setup(num_bytes,outfile):
    iv = os.urandom(int(num_bytes))
    with open(outfile, 'wb') as file:
        file.write(iv)
    
def encode(in_file,chave):
    
    with open(in_file, 'rb') as in_f, open(chave, 'rb') as chave_f, open(in_file + ".enc", 'wb') as out_f:
        while True:
            byte_in = in_f.read(1)
            byte_chave = chave_f.read(1)
            if not byte_in or not byte_chave:
                break
            xor_result = bytes([byte_in[0] ^ byte_chave[0]])
            out_f.write(xor_result)

def decode(in_file,chave):   
    
    with open(in_file, 'rb') as in_f, open(chave, 'rb') as chave_f, open(in_file + ".dec", 'wb') as out_f:
        while True:
            byte_in = in_f.read(1)
            byte_chave = chave_f.read(1)
            if not byte_in or not byte_chave:
                break
            xor_result = bytes([byte_in[0] ^ byte_chave[0]])
            out_f.write(xor_result)  

def main(inp):
    if (len(inp) != 4):
        print("Sem argumentos suficientes")
    else:
        if(inp[1]=='enc'):
            encode(inp[2],inp[3])
        if(inp[1]=='dec'):
            decode(inp[2],inp[3])
        if(inp[1]=='setup'):
            setup(inp[2],inp[3])
            
# Se for chamada como script...
if __name__ == "__main__":
    main(sys.argv)