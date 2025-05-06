import sys

def preproc(str):
      l = []
      for c in str:
          if c.isalpha():
              l.append(c.upper())
      return "".join(l)

def decifra(mensagem,cod):
    men = preproc(mensagem)
    l = []
    offset = ord(cod) - ord('A')  # Ir buscar offset
    for e in men:
        i = ord(e)
        i -= offset
        # Dar a volta ao alfabeto caso seja preciso
        if i < ord('A'):
            i += 26
        st = chr(i)
        l.append(st)
    return "".join(l)

def decifra_brute_force(mensagem, palavras):
    possible_offsets = ['A', 'B', 'C', 'D', 'E', 'F',
                        'G', 'H', 'I', 'J', 'K', 'L',
                        'M', 'N', 'O', 'P', 'Q', 'R', 'S',
                        'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

    for e in possible_offsets:
        msg = decifra(mensagem, e)
        is_sub = False
        for p in palavras:
            if p in msg:
                is_sub = True
                break  
        if is_sub:
            return (e, msg)
        
    return ("", "")

def main(inp):
    if (len(inp) < 3):
        print("Sem argumentos suficientes")
    else:
        bruteforce = decifra_brute_force(inp[1],inp[2:])
        if (bruteforce[0] != ""):
            print(bruteforce[0])
            print(bruteforce[1])

# Se for chamada como script...
if __name__ == "__main__":
    main(sys.argv)