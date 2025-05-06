
# Cria um programa em Python que tenha o seguinte comportamento:

# Pretende-se um programa que some todas as sequências de dígitos que encontre num texto;
# Prepara o programa para ler o texto do canal de entrada: stdin;
# Sempre que encontrar a string “Off” em qualquer combinação de maiúsculas e minúsculas, esse comportamento é desligado;
# Sempre que encontrar a string “On” em qualquer combinação de maiúsculas e minúsculas, esse comportamento é novamente ligado;
# Sempre que encontrar o caráter “=”, o resultado da soma é colocado na saída.
# Este exercício já foi proposto como TPC, mas agora deves tentar resolvê-lo usando um analisador léxico com condições de contexto.
import ply.lex as lex
import sys

# Lista de tokens
tokens = (
    'ON',
    'OFF',
    'ATRIB',
    'NUMBER',
    'OP'
)
# Estados
states = (
    ('ativa', 'exclusive'),
)

# Variável global para armazenar a soma
count = 0

# Operador padrão inicial (pode ser alterado durante a análise)
current_operator = '+'
    
# ----------REGRAS PARA ESTADO INICIAL ----------
# Regra para o token ON no estado inicial
def t_OP(t):
    r'[+*-\/]'
    pass

# Regras de expressão regular para os tokens no estado desativa
def t_NUMBER(t):
    r'\d+'
    pass
    
# ----------REGRAS PARA ESTADO ATIVO ----------
# Regra para o token ON no estado inicial
def t_ativa_OP(t):
    r'[+*-\/]'
    global current_operator
    current_operator = t.value
    return t
    
# Regras de expressão regular para os tokens no estado ativa
def t_ativa_NUMBER(t):
    r'\d+'
    global count, current_operator
    if current_operator == '+':
        lexer.count += int(t.value)
    elif current_operator == '-':
        lexer.count -= int(t.value)
    elif current_operator == '*':
        lexer.count *= int(t.value)
    elif current_operator == '/':
        lexer.count /= int(t.value)
    current_operator = '+'
    return t

# ----------REGRAS PARA TODOS ----------
# Regra para o token ON no estado inicial
def t_ANY_ON(t):
    r'(?i)on'
    t.lexer.begin('ativa')  # Muda para o estado 'ativa'
    
# Regra para o token OFF no estado inicial
def t_ANY_OFF(t):
    r'(?i)off'
    t.lexer.begin('INITIAL')  # Muda para o estado 'desativa'
    
# Regra para o token ATRIB em qualquer estado
def t_ANY_ATRIB(t):
    r'='
    print(f"Até agora o resultado é: {lexer.count}")
    return t

# Ignorar espaços em branco e quebras de linha
t_ANY_ignore = ' \t\n'

# Função de tratamento de erro
def t_ANY_error(t):
    print(f"Illegal character '{t.value[0]}' at index {t.lexpos}")
    t.lexer.skip(1)

# Criação do analisador léxico
lexer = lex.lex()
lexer.count = 0

# Código de entrada
codigo = ""
while True:
    # Lê uma linha da entrada padrão
    linha = sys.stdin.readline().strip()

    # Verifica se a palavra "STOP" foi inserida
    if linha.upper() == "STOP":
        break
    
    # Adiciona a linha ao código
    codigo += linha 

# Configura o analisador léxico com o código lido
lexer.input(codigo)

# Tokenização e exibição dos tokens
while True:
    token = lexer.token()
    if not token:
        break
