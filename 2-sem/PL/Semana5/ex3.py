texto = """ 
{
  "name": "John Doe",
  "age": 21,
  "gender": "male",
  "height": 1.68,
  "address": {
    "street": "123 Main Street",
    "city": "New York",
    "country": "USA",
    "zip": "10001"
  },
  "married": false,
  "hobbies": [
    {
      "name": "reading",
      "books": [
        {
          "title": "Heartstopper: Volume 1",
          "author": "Alice Oseman",
          "genres": ["Graphic Novels", "Romance", "Queer"]
        },
        {
          "title": "1984",
          "author": "George Orwell",
          "genres": ["Science Fiction", "Dystopia", "Politics"]
        }
      ]
    },
    {
      "name": "gaming",
      "games": [
        {
          "title": "Portal 2",
          "platform": ["PC", "PlayStation 3", "Xbox 360"]
        },
        {
          "title": "Synth Riders",
          "platform": ["PSVR", "PSVR2", "PCVR", "Oculus Quest"]
        }
      ]
    }
  ]
}
"""
import ply.lex as lex

tokens = (
    "ID",
    "RP1", #{
    "LP1", #}
    "RP2", #[
    "LP2", #] 
    "CONTSTR",
    "CONTNUM",
    "BOOL",
    "COMMA",
    "2PONTOS"
)

states = (
    ('dicionario', 'inclusive'),
    ('lista', 'inclusive')
 )

def t_CONTSTR(t):
    r'\s*"[\w :]+"'
    return t

def t_CONTNUM(t):
    r'\s*\d+(\.\d+)?'
    return t

def t_BOOL(t):
    r'\s*false|true'
    return t

def t_COMMA(t):
    r','
    return t

def t_2PONTOS(t):
    r':'
    return t

def t_ID(t):
    r'"[a-zA-Z_]+":'
    return t

def t_RP1(t):
    r'\{'
    t.lexer.P1 += 1
    t.lexer.begin('dicionario')
    return t

def t_RP2(t):
    r'\['
    t.lexer.P2 += 1
    t.lexer.begin('lista')
    return t

def t_ANY_LP1(t):
    r'\}'
    t.lexer.P1 -= 1
    t.lexer.begin('INITIAL')
    return t

def t_ANY_LP2(t):
    r'\]'
    t.lexer.P2 -= 1
    t.lexer.begin('INITIAL')
    return t

# Ignore whitespace
t_ignore = ' \t\n'

def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)

# Build the lexer
lexer = lex.lex()
lexer.P1 = 0
lexer.P2 = 0

lexer.input(texto)

while True:
    tok = lexer.token()
    if not tok:
        break
    print(tok)

if lexer.P1 == 0 and lexer.P2 == 0:
    print("All braces are properly balanced.")
else:
    print("Brace mismatch detected.")