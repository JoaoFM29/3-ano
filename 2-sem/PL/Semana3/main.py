import re

# exercicio 1.1
print("Linhas que contêm a palavra: hello no início (à esquerda)")
inputFromUser = input(">> ")
x = re.compile("hello")
while inputFromUser != "":
    if (x.match(inputFromUser)):
        print("A string começa com 'hello'")
        print(x.match(inputFromUser))
    else:
        print("A string não começa com 'hello'")
    inputFromUser = input("Digite outra linha (pressione enter para encerrar):\n>> ")

# exercicio 1.2
print("1. Linhas que contêm a palavra: hello")
x = re.compile("hello")
inputFromUser = input(">> ")
while inputFromUser != "":
    if (x.search(inputFromUser)):
        print("A string começa com 'hello'")
        print(x.search(inputFromUser))
    else:
        print("A string não começa com 'hello'")
    inputFromUser = input("Digite outra linha (pressione enter para encerrar):\n>> ")

# exercicio 1.3
print("1. Qualquer ocorrencia da palavra hello")
x = re.compile("(?i)hello")

inputFromUser = input(">> ")
while inputFromUser != "":
    if (x.findall(inputFromUser)):
        print("A string começa com 'hello'")
        print(x.findall(inputFromUser))
    else:
        print("A string não começa com 'hello'")
    inputFromUser = input("Digite outra linha (pressione enter para encerrar):\n>> ")

# exercicio 1.4
print("1. Qualquer ocorrencia da palavra hello é substituida por *YEP*")

inputFromUser = input(">> ")
while inputFromUser != "":
    x = re.sub("hello", "*YEP*", inputFromUser, count=0)
    print("Todas as ocorrências foram substituídas")
    print(x)

    inputFromUser = input("Digite outra linha (pressione enter para encerrar):\n>> ")

# exercicio 1.5
print("1. Divide a string pelo char ',' ")
inputFromUser = input(">> ")

while inputFromUser != "":
    x = re.split(",", inputFromUser, maxsplit=0)
    print("A string foi separada corretamente pelo char ',' ")
    print(x)

    inputFromUser = input("Digite outra linha (pressione enter para encerrar):\n>> ")


# exercício 2
def palavra_magica(frase):
    while frase != "":
        return re.search(("por[\s]+favor[.?!]$"), frase)


print(palavra_magica("Posso ir à casa de banho, por  favor?"))
print(palavra_magica("Preciso de um favor."))


# exercicio 3
def narcissismo(linha):
    x = re.compile("(\b?i:eu\b)")
    while linha:
        return len(re.findall(x, linha))


print(narcissismo(
    "Eu não sei se eu quero continuar a ser eu. Por outro lado, eu ser eu é uma parte importante de quem EU sou."))


# exercicio 4
def troca_de_curso(linha, novo_curso):
    x = re.compile("LEI")
    while linha:
        return re.sub(x, novo_curso, linha, 0)


fonte = "LEI é o melhor curso! Adoro LEI! Gostar de LEI devia ser uma lei."
curso = input("Novo curso? ")
print(troca_de_curso(fonte, curso))


# exercício 5
def soma_string(linha):
    numeros = re.split(",", linha, maxsplit=0)
    soma = 0
    for numero in numeros:
        soma += int(numero)
    return soma


print(soma_string("4,10,-6,2,3,8,-3,0,2,-5,1"))


# exercicio 6
def pronomes(frase):
    x = re.compile("(\b?i:eu|tu|ele|nós|vós|eles|elas\b)")
    result = re.findall(x, frase)
    return result


pslist = pronomes(
    "Ola eu vou de certeza. Tu tu e ele, vêm? Eu não espero por vós. Eu estou com pressa, ele tem de vir!")
print(pslist)


# exercício 7
def variavel_valida(id):
    x = re.compile("^[\w]*$")
    resultado = re.findall(x, id)
    return resultado


print(variavel_valida("aa11_aaaa"))

#exercício 8
fonte = """
123 ddddd;
+345.77 gkmrm;
8766 yyyyy;
-1234 +3ddd4 -15
fim
"""


def extrai_inteiros(texto):
    inteiros = []
    inteiro = re.compile("^[+|-]?[0-9]$")
    for char in texto:
        if(re.match(inteiro, char)):
            inteiros.append(inteiro)
    return inteiros


print(extrai_inteiros(fonte))


#exercício 9
def underscores(frase):
    resultado = re.sub(r'\s+', '_', frase)
    return resultado

print(underscores("Aqui temos   um belo  exemplo   de frase!"))

#exercicio 10
lista = [
    "4700-000",
    "1234-567",
    "8541-543",
    "4123-974",
    "9481-025"
]
lista2 = "1100-3#1234-777#1198-999#4715-012"

def codigos(listaCPs):
    x = re.compile("^[0-9]{4}-[0-9]{3}$")
    resultado = []
    for l in listaCPs:
        res = re.findall(x, l)
        if res:
            resultado.append(tuple(res[0].split('-')))
    return resultado


print(codigos(lista))
print(codigos(re.split(r'#',lista2)))