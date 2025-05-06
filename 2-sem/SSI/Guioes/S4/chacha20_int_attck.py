import sys
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms


def chacha20_attack(enc,pos,txt_at_pos,ntxt_at_pos):
    with open(enc,'rb') as enc_file:
        nonce = enc_file.read(16)
        ct = enc_file.read()
    
    target = ct[int(pos)]
    new_ct_at_pos = (ord(ntxt_at_pos) ^ target) ^ ord(txt_at_pos)

    byte_list = list(ct)
    byte_list[int(pos)] = new_ct_at_pos

    updated_ct = bytes(byte_list)

    new_enc_file = open(enc + '.attack', 'wb')
    new_enc_file.write(nonce)
    new_enc_file.write(updated_ct)
    

def main(inp):

    if (len(inp) != 5):
        print("Erro nos argumentos")
    else:
        chacha20_attack(inp[1],inp[2],inp[3],inp[4])
            
# Se for chamada como script...
if __name__ == "__main__":
    main(sys.argv)