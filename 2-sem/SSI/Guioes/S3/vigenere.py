import sys

def preproc(str):
      l = []
      for c in str:
          if c.isalpha():
              l.append(c.upper())
      return "".join(l)


def cifra_cesar(mensagem, cod):
    men = preproc(mensagem)
    l = []
    offset = ord(cod) - ord('A')  # Ir buscar offset
    for e in men:
        i = ord(e)
        i += offset
        # Dar a volta ao alfabeto caso seja preciso
        if i > ord('Z'):
            i -= 26
        st = chr(i)
        l.append(st)
    return "".join(l)

def decifra_cesar(mensagem,cod):
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

def cifra_vigenere(mensagem,codString):
    mensagem = preproc(mensagem)
    atual = 0
    l = []
    for e in mensagem:
        if (atual > len(codString)-1):
            atual = 0
        new = cifra_cesar(e,codString[atual])
        l.append(new)
        atual+=1
    return "".join(l)

def decifra_vigenere(mensagem,codString):
    mensagem = preproc(mensagem)
    atual = 0
    l = []
    for e in mensagem:
        if (atual > len(codString)-1):
            atual = 0
        new = decifra_cesar(e,codString[atual])
        l.append(new)
        atual+=1
    return "".join(l)     

def main(inp):
    if (len(inp) != 4):
        print("Sem argumentos suficientes")
    else:
        if(inp[1]=='enc'):
            a = cifra_vigenere(inp[3],inp[2])
            print(a)
        if(inp[1]=='dec'):
            a = decifra_vigenere(inp[3],inp[2])
            print(a)

# Se for chamada como script...
if __name__ == "__main__":
    main(sys.argv)