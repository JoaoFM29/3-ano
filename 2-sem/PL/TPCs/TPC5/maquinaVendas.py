import json
import sys
import ply.lex as lex
from datetime import datetime

global saldo
saldo = 0.0

# Nome do arquivo JSON
nome_arquivo = 'stock.json'

# Abre o arquivo JSON
with open(nome_arquivo, 'r') as file:
    # Carrega o conteúdo do arquivo JSON
    dados_json = json.load(file)

# Obtenha a data e hora atual
data_hora_atual = datetime.now()

# Formate a data e hora como uma string
data_hora_formatada = data_hora_atual.strftime("%d/%m/%Y %H:%M:%S")

print("maq: " + data_hora_formatada + ", Stock carregado, Estado atualizado.")
print("maq: Bom dia. Estou disponível para atender o seu pedido.")
print("Escolha um dos numeros dos comandos disponiveis:")
print("LISTAR | SAIR | MOEDA (2e 1e 50c 20c 10c 5c) | SELECIONAR (codigo produto)")

tokens=(
    "LISTAR",
    "SAIR",
    "MOEDA",
    "SELECIONAR",
    "TEXTO"
)

states = (
    ('inserirMoeda', 'inclusive'),
    ('selecionaProd', 'inclusive')
)

def t_SAIR(t):
    r'SAIR'
    global saldo
    saldo = 0.0
    print("maq: Até à próxima!")
    
    sys.exit(0) 
    
def t_MOEDA(t):
    r'MOEDA'
    t.lexer.begin("inserirMoeda")
    return t

def t_SELECIONAR(t):
    r'SELECIONAR'
    t.lexer.begin("selecionaProd")
    return t

def t_LISTAR(t):
    r'LISTAR'
    listarProdutos()
    return t

def t_inserirMoeda_TEXTO(t):
    r'\d\d?[ec]{1}?'
    global saldo
    saldo += float(t.value[:-1])
    return t
    
def t_selecionaProd_TEXTO(t):
    r'[A-Z]\d\d'
    venderProduto(t.value)
    return t
    
# Função de tratamento de erro
def t_error(t):
    print(f"Illegal character '{t.value[0]}' at index {t.lexpos}")
    t.lexer.skip(1)
    
def listarProdutos():
    print("=======================================================")
    print("             MÁQUINA DE VENDAS             ")
    print("=======================================================")
    print(" Código   |          Produto        |  Preço |  Quant ")
    print("=======================================================")

    for item in dados_json["stock"]:
        cod = item['cod']
        nome = item['nome']
        quant = item['quant']
        preco = item['preco']
        
        print(f"|  {cod}    | {nome.ljust(23)} |  {preco} € |    {str(quant).rjust(2)}    |")

    print("=======================================================")
    print("LISTAR | SAIR | MOEDA (2e 1e 50c 20c 10c 5c) | SELECIONAR (codigo produto)")
    
def venderProduto(codigoProduto):
    global saldo
    preco = None
    nome = None

    # Procura o item com o código
    for item in dados_json["stock"]:
        if item["cod"] == codigoProduto:
            preco = item["preco"]
            nome = item["nome"]
        pass
    if preco > saldo:
        print("maq: Saldo insufuciente para satisfazer o seu pedido")
        print(f"maq: Saldo = {saldo}c; Pedido = {preco}c")
    elif preco == saldo:    
        for item in dados_json["stock"]:
            if item["cod"] == codigoProduto:
                item["quant"] -= 1
            pass
        saldo = 0.0
        print(f"maq: Pode retirar o produto dispensado: \"{nome}\"")
        print(f"Saldo: {saldo}c")
    else:   
        moedas = calcular_troco((saldo-preco)*100)
        moedas_texto = [formatar_moeda(moeda) for moeda in moedas]
        for item in dados_json["stock"]:
            if item["cod"] == codigoProduto:
                item["quant"] -= 1
            pass
        saldo = 0.0
        print(f"maq: Pode retirar o produto dispensado: \"{nome}\"")
        print(f"maq: Pode retirar o troco: {' ,'.join(moedas_texto)}")
        print("LISTAR | SAIR | MOEDA (2e 1e 50c 20c 10c 5c) | SELECIONAR (codigo produto)")
        
        
def calcular_troco(valor_troco_em_centimos):
    moedas_disponiveis = [200, 100, 50, 20, 10, 5]  # Valores das moedas em centimos
    troco = []
    
    for moeda in moedas_disponiveis:
        while valor_troco_em_centimos >= moeda:
            troco.append(moeda)
            valor_troco_em_centimos -= moeda

    return troco

def formatar_moeda(valor_em_centimos):
    if valor_em_centimos >= 100:
        return f"{valor_em_centimos // 100}€"
    else:
        return f"{valor_em_centimos}c"
    
# Ignorar espaços em branco e quebras de linha
t_ignore = ' \t\n'
# Criação do analisador léxico
lexer = lex.lex()

# Configura o analisador léxico com o código lido
programa = True
while programa:
    # Lê uma linha da entrada padrão
    linha = sys.stdin.readline().strip()
    lexer.input(linha)

    # Tokenização e exibição dos tokens
    while True:
        token = lexer.token()
        if not token:
            break
    
    
    



