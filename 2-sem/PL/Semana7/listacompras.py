import ply.yacc as yacc
import ply.lex as lex

text= """
CARNE :
  - 1 :: Bife :: 10.00 :: 1;
  - 2 :: Panado :: 5.00 :: 4;
  - 3 :: Hamburguer :: 8.00 :: 3;
  - 4 :: Almondegas :: 7.00 :: 5;

BEBIDA :
  - 5 :: Agua :: 0.40 :: 16;
  - 6 :: Sumo :: 1.50 :: 9;
  - 7 :: Refrigerante :: 1.80 :: 10;

FRUTA :
  - 8 :: Maca :: 0.60 :: 20;
  - 9 :: Banana :: 0.50 :: 15;
  - 10 :: Laranja :: 0.80 :: 18;
  - 11 :: Pessego :: 0.70 :: 22;
  - 12 :: Uva :: 0.90 :: 17;

LEGUMES :
  - 13 :: Alface :: 1.00 :: 25;
  - 14 :: Tomate :: 0.75 :: 23;
  - 15 :: Cebola :: 0.50 :: 28;
  - 16 :: Batata :: 0.30 :: 30;
  - 17 :: Cenoura :: 0.40 :: 26;

PASTELARIA :  
  - 18 :: Bolo de Chocolate :: 3.50 :: 1;
  - 19 :: Croissant :: 1.20 :: 14;
  - 20 :: Pastel de Nata :: 1.00 :: 5;
  - 21 :: Donut :: 0.80 :: 13;
"""

# GIC = <T, N, S, P>

# T = {TRACO NUMERO COLONS TIPO PVIRG PRECO QUANTIDADE}
# N = {categorias categoria entrada}
# S = categorias
#         categorias -> CATEGORIA COLONS entrada categorias
#                    | vazio
#         entrada -> TRACO NUMERO COLONS TIPO COLONS PRECO COLONS QUANTIDADE PVIRG entrada
#                    | vazio

# Tokens
tokens = (
    'CATEGORIA',
    'COLONS',
    'TRACO',
    'NUMERO',
    'TIPO',
    "PVIRG"
)

t_CATEGORIA = r'[A-Z]+'  # Uma palavra com a primeira letra maiúscula seguida de letras minúsculas opcionais
t_PVIRG = r'\;'
t_TRACO = r'\-'
t_COLONS = r'\:{1,2}'

def t_TIPO(t):
    r'[A-Z][a-z]+(\s[a-z]*\s[A-Z][a-z]+)?'
    return t

def t_NUMERO(t):
    r'\d+(\.\d+)?'
    t.value = float(t.value)
    return t

t_ignore = ' \n\t'

# Erro de token
def t_error(t):
    print(f"Token found: {t.type} -> {t.value}")
    t.lexer.skip(1)

# Construção da gramática
def p_categorias(p):
    'categorias : CATEGORIA COLONS entrada categorias'
    p[0] = {'CATEGORIA': p[1],
            'ENTRADA-CATE': p[3]
        }
def p_entrada(p):
    'entrada : TRACO NUMERO COLONS TIPO COLONS NUMERO COLONS NUMERO PVIRG entrada'
    p[0] = {
        'NUMERO': int(p[2]),
        'TIPO': p[4].strip(),
        'PRECO': float(p[6]),
        'QUANTIDADE': int(p[8]),
        'ENTRADA': p[10]
    } 
    
def p_categorias_empty(p):
    'categorias : empty'
    p[0] = None
    
def p_entrada_empty(p):
    'entrada : empty'
    p[0] = None

# Definindo o token EMPTY
def p_empty(p):
    'empty :'
    pass

def p_error(p):
    if p:
        print(f"Syntax error at token '{p.value}' of type {p.type}")
    else:
        print("Syntax error at EOF")
        
# Build the lexer
lexer = lex.lex()

# Build the parser
parser = yacc.yacc()

resultado = parser.parse(text, lexer=lexer)
print(resultado)

