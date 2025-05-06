import ply.yacc as yacc
import ply.lex as lex

# Rui : [10,15]
# Tiago : [15,12,13,14]

# GIC = <T, N, S, P>

# T = {NOME, ":", NOTA, "[", "]"}
# N = {frase, notas, notas2}
# S = frase

#         frase -> NOME COLON LBRACKET NOTA notas RBRACKET
#                | EMPTY
#         notas -> NOTA COMMA notas
#                | NOTA
#                | EMPTY

# Tokens
tokens = (
    'NOME',
    'NOTA',
    'COLON',
    'LBRACKET',
    'RBRACKET',
    'COMMA', 
)

t_COLON = r'\:'
t_LBRACKET = r'\['
t_RBRACKET = r'\]'
t_COMMA = r'\,'

t_ignore = ' \n\t'

def t_NOME(t):
    r'[A-Za-z]+'
    return t

def t_NOTA(t):
    r'\d+'
    t.value = int(t.value)
    return t

# Erro de token
def t_error(t):
    print("Caractere ilegal '%s'" % t.value[0])
    t.lexer.skip(1)

# Construção da gramática
def p_frase(p):
    'frase : NOME COLON LBRACKET notas RBRACKET'
    p[0] = (p[1], p[4])
        
def p_notas(p):
    'notas : NOTA notas2'
    p[0] = [p[1]] , p[2]
    
def p_notas2(p):
    'notas2 : COMMA NOTA notas2'
    p[0] = [p[2]] , p[3]
    
def p_notas2_empty(p):
    'notas2 : empty'
    p[0] = None


# Definindo o token EMPTY
def p_empty(p):
    'empty :'
    pass

def p_error(p):
    if p:
        print("Erro de sintaxe em '%s'" % p.value)
    else:
        print("Erro de sintaxe no fim da entrada")

# Build the lexer
lexer = lex.lex()

# Build the parser
parser = yacc.yacc()

while s := input('calc > '):
    resultado = parser.parse(s, lexer=lexer)
    print(resultado)