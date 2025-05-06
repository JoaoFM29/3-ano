import ply.lex as lex

texto = """
SELECT * FROM users WHERE age > 18
SELECT * FROM employees
SELECT name, salary FROM employees WHERE department = 'IT'
SELECT product_name, price FROM products WHERE category = 'Electronics' AND price < 500
SELECT customer_name, order_date, total_amount FROM orders WHERE total_amount > 1000 ORDER BY order_date DESC
SELECT customers.customer_name, orders.order_date FROM customers JOIN orders ON customers.customer_id = orders.customer_id
"""

# Especificação dos tokens
token_specification = [
    ('NUM',   r'\d+\.?\d+'),       
    ('WHERE', r'WHERE'),
    ('SELECT', r'SELECT'),
    ('FROM', r'FROM'),
    ('COMMA', r','),
    ('ORDERBY', r'ORDER\sBY'),
    ('ORDEM', r'DESC|ASC'),
    ('JOIN', r'JOIN'),
    ('AND', r'AND'),
    ('ON', r'ON'),
    ('ATRIB', r'='),              
    ('ID',    r'[_a-zA-Z.\']+'),         
    ('TUDO', r'\*'),
    ('OP',    r'[+\-*\/><=]'),     
    ('NEWLINE', r'\n'),           
    ('SKIP', r'[ \t]+'),           
    ('error', r'.'),                
]

#lista de token 
tokens = [token[0] for token in token_specification]

# Função para lidar com o SELECT
def t_SELECT(t):
    r'SELECT'
    return t

# Função para lidar com o WHERE
def t_WHERE(t):
    r'WHERE'
    return t

# Função para lidar com o FROM
def t_FROM(t):
    r'FROM'
    return t

# Função para lidar com o ORDER BY
def t_ORDERBY(t):
    r'ORDER\sBY'
    return t

# Função para lidar com o DESC ou ASC
def t_ORDEM(t):
    r'DESC|ASC'
    return t

# Função para lidar com o JOIN
def t_JOIN(t):
    r'JOIN'
    return t

# Função para lidar com o ON
def t_ON(t):
    r'ON'
    return t

# Função para lidar com o AND
def t_AND(t):
    r'AND'
    return t

# Função para tratar caracteres ignorados
def t_SKIP(t):
    r'[ \t]+'
    pass

# Função para tratar quebras de linha
def t_NEWLINE(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# Função para lidar com números
def t_NUM(t):
    r'\d+\.?\d+'
    t.value = float(t.value) if '.' in t.value else int(t.value)
    return t

# Função para lidar com operadores de atribuição
def t_ATRIB(t):
    r'='
    return t

# Função para lidar com identificadores
def t_ID(t):
    r'[_a-zA-Z.\']+'
    return t

# Função para lidar com operadores aritméticos
def t_OP(t):
    r'[+\-*\/><=]'
    return t

# Função para lidar com a vírgula (,)
def t_COMMA(t):
    r','
    return t

# Função para lidar com erros
def t_error(t):
    r'.'
    print(f"Illegal character '{t.value[0]}' at line {t.lineno}, position {t.lexpos}")
    t.lexer.skip(1)

# Regras para as frases específicas 
def t_QUERY(t):
    r'SELECT TUDO FROM ID WHERE ID OP(OP)* NUM|' \
    r'SELECT TUDO FROM ID|' \
    r'SELECT ID (COMMA ID)* FROM ID WHERE ID ATRIB ID|' \
    r'SELECT ID (COMMA ID)* FROM ID WHERE ID ATRIB ID AND ID OP NUM|' \
    r'SELECT ID (COMMA ID)* FROM ID WHERE ID OP NUM ORDERBY ID ORDEM|' \
    r'SELECT ID (COMMA ID)* FROM ID JOIN ON ID ATRIB ID'
    return t


# Crie o analisador léxico
lexer = lex.lex()

# Adicione a string de entrada ao analisador léxico
lexer.input(texto)

# Percorra os tokens e imprima informações
while True:
    tok = lexer.token()
    if not tok:
        break  # Não há mais tokens
    print(f"Token: {tok.type}, Value: {tok.value}, Line: {tok.lineno}, Position: {tok.lexpos}")