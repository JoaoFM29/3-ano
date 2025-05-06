from itertools import product
from collections import Counter
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

def generate_strings(possibilidades, current_index, current_string, result):
    if current_index == len(possibilidades):
        result.append(current_string)
        return
    for letter in possibilidades[current_index]:
        generate_strings(possibilidades, current_index + 1, current_string + letter, result)

def generate_all_possible_strings(possibilidades):
    result = []
    generate_strings(possibilidades, 0, "", result)
    return result

def decifra_frequencia(mensagem,palavras,tam):
    
    letras_comuns_pt = ['A', 'E', 'O', 'S', 'R', 'I', 'D', 'M', 'N', 'T','C','U','I']
    alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    possibilidades = {} # aqui vou guardar por cada indice da chave quais as letras mais provaveis

    # Determina chaves possiveis ao analisar as fatias da mensagem (tendo em conta o 'tam')
    for i in range(tam):
        
        slice_text = mensagem[i::tam] # buscar de 3 em 3 as letras
        counter = Counter(slice_text)
        most_frequent_26 = counter.most_common(26)
        lista = set()
        
        if abs(most_frequent_26[0][1] - most_frequent_26[1][1]) / len(slice_text) <= 0.1:
            
            lista.add(alfabeto[((ord(most_frequent_26[0][0])-ord('A')) % 26)])
            lista.add(alfabeto[((ord(most_frequent_26[0][0])-ord('E')) % 26)])
            lista.add(alfabeto[((ord(most_frequent_26[1][0])-ord('A')) % 26)])
            lista.add(alfabeto[((ord(most_frequent_26[1][0])-ord('E')) % 26)])
        else:
            lista.add(alfabeto[((ord(most_frequent_26[0][0])-ord('A')) % 26)])
            lista.add(alfabeto[((ord(most_frequent_26[0][0])-ord('E')) % 26)])
            
        possibilidades[i] = lista
    
    todas_as_combinacoes = generate_all_possible_strings(possibilidades)
    
    for e in todas_as_combinacoes:
        msg = decifra_vigenere(mensagem, e)
        is_sub = False
        for p in palavras:
            if p in msg:
                is_sub = True
                break  
        if is_sub:
            return (e, msg)
        
        
         
       
    
    
def main(inp):
    if (len(inp) < 3):
        print("Sem argumentos suficientes")
    else:
        bruteforce = decifra_frequencia(inp[2],inp[3:],int(inp[1]))
        if (bruteforce[0] != ""):
            print(bruteforce[0])
            print(bruteforce[1])
        
# Se for chamada como script...
if __name__ == "__main__":
    main(sys.argv)