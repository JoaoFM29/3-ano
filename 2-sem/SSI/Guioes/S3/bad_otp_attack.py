import sys
import random


def check_plaintext(textoCifrado, palavra):
    p = palavra.encode()
    return p in textoCifrado

def decode(in_file,chave):   
    
    with open(in_file, 'rb') as in_f:
        i = 0
        xor_result =b""
        while True and i < len(chave):
            byte_in = in_f.read(1)
            byte_chave = chave[i]
            i+=1
            if not byte_in or not byte_chave:
                break
            xor_result += bytes([byte_in[0] ^ byte_chave])
            
        return(xor_result) 
    
def generate_all_possible_seeds():
    """Generate all possible combinations of random.randbytes(2)."""
    seeds = []
    for byte1 in range(256):
        for byte2 in range(256):
            seed = bytes([byte1, byte2])
            seeds.append(seed)
    return seeds

def bad_prng(n,seed):
    """ an INSECURE pseudo-random number generator """
    random.seed(seed)
    return random.randbytes(n)

def bad_otp_attack(cifra, palavras):
    
    with open(cifra, 'rb') as f:
        t = len(f.read())+1; # isto acaba por ser inútil
    
    chaves = generate_all_possible_seeds()
    for i in range(t,t*3):
        for k in chaves: # assumi que sabia antes que a seed ia ser de 2 bytes apenas
            chave_a_testar = bad_prng(i,k) # por alguma razão temos de saber o tamanho da chave usada também
            men = decode(cifra,chave_a_testar) # mais ou menos só
            for palavra in palavras:
                if check_plaintext(men,palavra):
                    return men.decode()
        
def main(inp):
    
    if len(inp) < 3:
        print("Sem argumentos suficientes")
    else:
        print(bad_otp_attack(inp[1], inp[2:]))

if __name__ == "__main__":
    main(sys.argv)
