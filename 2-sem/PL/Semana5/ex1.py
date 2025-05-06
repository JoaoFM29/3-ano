import ply.lex as lex
import sys

# Lista de tokens
tokens = (
    'VAR',
    'OP',
    'ATRIB',
    'NUMERO',
    'SPACE'
)

# Regras de expressão regular para os tokens. Tem que começar sempre com "t_"
t_ATRIB = r'\='


# Regra para tratar números inteiros
def t_NUMERO(t):
    r'\d+'
    t.value = int(t.value)
    return t

def t_VAR(t):
    r'[a-zA-Z_][a-zA-Z0-9_]*'
    print(t.value + "\n")
    return t

def t_OP(t):
    r'[*\/\-+]'
    print("Operador encontrado, " + t.value + "\n")
    return t

# Regra para tratar quebras de linha
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)
    print("\n")
    
# Regra para tratar os espaços
def t_SPACE(t):
    r'\s+'
    pass

def t_error(t):
    print(f"Illegal character '{t.value[0]}' at index {t.lexpos}")
    t.lexer.skip(1)
    
# Exemplo de uso
codigo = """x=a+1
b=2
a = b-1
a*=2"""

codigo = ""
while True:
    # Lê uma linha da entrada padrão
    linha = sys.stdin.readline().strip()

    # Adiciona a linha ao código
    codigo += linha 

    # Verifica se a palavra "STOP" foi inserida
    if linha == "STOP":
        break

# Criação do analisador léxico
lexer = lex.lex()

# Configura o analisador léxico com o código lido
lexer.input(codigo)

# Tokenização e exibição dos tokens
while True:
    token = lexer.token()
    if not token:
        break