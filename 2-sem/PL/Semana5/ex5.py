# Desenvolva um analisador léxico capaz de ler um ficheiro de texto e ignorar todo o texto dentro de comentários inline (desde "//" até ao fim de linha)
# e todo o texto dentro de comentários multiline (desde "/*" até "*/").

# Note que deve suportar convenientemente comentários dentro de comentários, conforme exemplificado abaixo

codigo = """
/* comment */ ola1

/* comment****comment */ ola2 /*
comment
comment
****/ ola3

/*********/

ola4
 mais um pouco // remover comentário inline
FIM
"""

import ply.lex as lex
import sys

count = 0

tokens = (
    'FCOMMENT',
    'LCOMMENT',
    'TEXTO'
)

states=(
    ('Lcomentario', 'exclusive'),
    ('Fcomentario', 'exclusive'),
)

def t_TEXTO(t):
    r'[\w ]+'
    t.value = t.lexer.lexmatch.group(1)
    print(t.value)
    t.lexer.begin('INITIAL') 
    return t

# Muda para o estado 'comentario'
def t_ANY_FCOMMENT(t):
   r'\/\*+?'
   t.lexer.begin('Fcomentario')  
   return t

# Muda para o estado 'comentario'
def t_ANY_LCOMMENT(t):
   r'\/\/'
   t.lexer.begin('Lcomentario') 
   return t

#REGRA PARA O COMENTARIO EM LINHA
def t_Lcomentario_TEXTO(t):
    r'[^\n]+'
    t.lexer.begin('INITIAL')  # Muda para o estado 'texto' 
    pass

#REGRA PARA O COMENTARIO EM MULTINHA
def t_Fcomentario_TEXTO(t):
    r'([\s\S]*?)\*\/'
    t.lexer.begin('INITIAL')  # Muda para o estado 'texto' 
    pass

# Ignorar espaços em branco e quebras de linha
t_ANY_ignore = '\n'

# Função de tratamento de erro
def t_ANY_error(t):
    print(f"Illegal character '{t.value[0]}' at index {t.lexpos}")
    t.lexer.skip(1)

# Criação do analisador léxico
lexer = lex.lex()

# Configura o analisador léxico com o código lido
lexer.input(codigo)

# Tokenização e exibição dos tokens
while True:
    token = lexer.token()
    if not token:
        break
    print(token)