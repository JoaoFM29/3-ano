import re
import sys

#Exercício 1
texto = """A 03/01/2022, Pedro viajou para a praia com a sua família.
Eles ficaram hospedados num hotel e aproveitaram o sol e o mar durante toda a semana.
Mais tarde, no dia 12/01/2022, Pedro voltou para casa e começou a trabalhar num novo projeto.
Ele passou muitas horas no escritório, mas finalmente terminou o projeto a 15/01/2022."""

def trocaData(texto):
    data = re.compile(r"([0-3][0-9])\/([0-1][0-9])\/(\d{4})")
    for palavra in texto.split(" "):#fazer sub
        if(re.match(data, palavra)):
            texto = re.sub(data, r'\3/\2/\1', texto)
    return texto
    
print(trocaData(texto))

#Exercício 2
file_names = [
  "document.txt", # válido
  "file name.docx", # inválido
  "image_001.jpg", # válido
  "script.sh.txt", # válido
  "test_file.txt", # válido
  "file_name.", # inválido
  "my_resume.docx", # válido
  ".hidden-file.txt", # válido
  "important-file.text file", # inválido
  "file%name.jpg" # inválido
]

def validaNome(lista):
    resultado = {}
    nome = re.compile(r"([\w.-]+)\.([a-zA-Z]+)")
    for n in lista:
        match = re.match(nome, n)
        if match:
            extensao = match.group(2)
            if extensao in resultado:
                resultado[extensao].append(f"{n} é válido")
            else:
                resultado[extensao] = [f"{n} é válido"]
    return resultado
    
print(validaNome(file_names))

#Exercício 3
lista = [
    "4700-000", # válido
    "9876543", # inválido
    "1234-567", # válido
    "8x41-5a3", # inválido
    "84234-12", # inválido
    "4583--321", # inválido
    "9481-025" # válido
]

def codPostal(lista):
    pares = []
    x = re.compile(r"^([0-9]{4})-([0-9]{3})$")

    for codigo in lista:
        match = re.match(x,codigo)
        if match:
            pares.append((match.group(1), match.group(2)))
    return pares

print(codPostal(lista))

#Exercício 4
abreviaturas = {
    "UM": "Universidade do Minho",
    "LEI": "Licenciatura em Engenharia Informática",
    "UC": "Unidade Curricular",
    "PL": "Processamento de Linguagens"
}


texto = "A /abrev{UC} de /abrev{PL} é muito fixe! É uma /abrev{UC} que acrescenta muito ao curso de /abrev{LEI} da /abrev{UM}."

def abrev(abreviaturas, texto):
    sigla = re.compile(r'(\/abrev{)([A-Z]+)(})')
    resultado = re.sub(sigla, lambda match: abreviaturas.get(match.group(2)), texto) # a expressão regular retorna o match
    return resultado

print(abrev(abreviaturas, texto))

#Exercício 5
matriculas = [
    "AA-AA-AA", # inválida
    "LR-RB-32", # válida
    "1234LX", # inválida
    "PL 22 23", # válida
    "ZZ-99-ZZ", # válida
    "54-tb-34", # inválida
    "12 34 56", # inválida
    "42-HA BQ" # válida, mas inválida com o requisito extra
]
def validaM(matriculas):
    resultado = ""
    validar = re.compile(r'([A-Z\d]{2})[- ]([A-Z\d]{2})[- ](?!\2)([A-Z\d]{2})|([A-Z\d]{2})[- ]([A-Z\d]{2})[- ](?!\4)([A-Z\d]{2})')
    for m in matriculas:
        if(re.match(validar, m)):
            resultado += m +"\n"
    return resultado

print(validaM(matriculas))

#Exercício 6
texto = """Num lindo dia de [ESTAÇÃO DO ANO], [NOME DE PESSOA] foi passear com o seu [EXPRESSÃO DE PARENTESCO MASCULINA].
Quando chegaram à [NOME DE LOCAL FEMININO], encontraram um [OBJETO MASCULINO] muito [ADJETIVO MASCULINO].
Ficaram muito confusos, pois não conseguiam identificar a função daquilo.
Seria para [VERBO INFINITIVO]? Tentaram perguntar a [NOME DE PESSOA FAMOSA], que também não sabia.
Desanimados, pegaram no objeto e deixaram-no no [NOME DE LOCAL MASCULINO] mais próximo.
Talvez os [NOME PLURAL MASCULINO] de lá conseguissem encontrar alguma utilidade para aquilo."""

def subSpace(texto):
    espaço = re.compile(r'\[([A-Za-zÇãâÃç\s]+)\]')
    correspondencias = espaço.finditer(texto)
    for correspondencia in correspondencias:
        
        entrada_usuario = input(f"Digite algo para o campo [{correspondencia.group(1)}]: ")
        novo_texto = espaço.sub(entrada_usuario, texto, 1)
    return novo_texto

print(subSpace(texto))

texto = "Este e um um exemplo de texto texto para verificar um o programa. Este programa exemplo exemplo tem que remover as repeticoes das palavras um texto."
#Exercício 7
def remRep(texto):
    palavrasRep = []
    result = ""
    for palavra in texto.split(" "):
        if palavra not in palavrasRep :
            palavrasRep.append(palavra)
    for palavra in palavrasRep:
        result += palavra + ' '
    return result

print(remRep(texto))

def remRepReg(texto):
    iter = re.finditer(r'[a-zA-Z0-9]+', texto)
    frase = []
    result = ''
    for palavra in iter:
        if palavra.group() not in frase :
            frase.append(palavra.group())
    result += ' '.join(frase)
    return result

print(remRepReg(texto))
