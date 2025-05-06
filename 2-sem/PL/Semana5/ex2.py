import ply.lex as lex

text="""
@techreport{Camila,
  author ={{projecto Camila}},
  editor ={L.S. Barbosa and J.J. Almeida and J.N. Oliveira and Luís Neves},
  title = "\textsc{Camila} - A Platform for Software Mathematical Development",
  url="http://camila.di.uminho.pt",
  type="(Páginas do projecto)",
  institution = umdi,
  year=1998,
  keyword = "FS",
}
"""
# Lista de tokens
tokens=(
    'AROB',
    'TEXT',
    'PALAVRAS',
    'URL',
    'RCHAVETA',
    'LCHAVETA',
    'RPARENT',
    'LPARENT',
    'ASPA',
    'NUMERO',
    'ATRIB',
    'VIRGULA',
    'COMMA',

)

# Regras de expressão regular para os tokens. Tem que começar sempre com "t_"
t_AROB = r'@'
t_VIRGULA = r','
t_ASPA = r'"'
t_COMMA = r'\.'
t_RCHAVETA = r'{'
t_LCHAVETA = r'}'
t_RPARENT = r'\('
t_LPARENT = r'\)'
t_ATRIB = r'='
t_TEXT = r'"[^"]+"'
t_PALAVRAS = r'[a-zA-Z]+\s*'
t_URL = r'"(http[s]?:\/\/.+?)"'

# Regra para tratar quebras de linha
def t_NUMERO(t):
    r'\d+'
    t.value = int(t.value)
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

# Regra para tratar as palavras desconhecidas
def t_error(t):
    print(f"Illegal character '{t.value[0]}' at index {t.lexpos}")
    t.lexer.skip(1)
    print("Encerrando o programa devido a erro de sintaxe.")
    exit()

# Criação do analisador léxico
lexer = lex.lex()

# Configura o analisador léxico com o código lido
lexer.input(text)

# Tokenização e exibição dos tokens

while True:
    token = lexer.token()
    if not token:
        break
    print(token)