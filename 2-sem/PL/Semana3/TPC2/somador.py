import re

on = True
numeros=[]

#Expressões regulares
inteiros = re.compile("^([+-]?\d+)(\.\d+)?$")

#função auxiliar que soma os numeros armazenados
def soma(lista):
    resultado = 0
    for num in lista:
        resultado += int(num)
    return resultado

# Ler o conteúdo do ficheiro .txt
with open("teste.txt", "r") as file:
    conteudo = file.readlines()   
    
# tratar da informação do ficheiro
for linha in conteudo:
    palavras = linha.split()
    for palavra in palavras:
        if re.match(inteiros, palavra) and on == True:
            numeros.append(palavra)
        elif re.match("(?i:on)", palavra) :
            on = True
        elif re.match("(?i:off)", palavra) :
            on = False
        elif re.match("=", palavra):
            print(soma(numeros))