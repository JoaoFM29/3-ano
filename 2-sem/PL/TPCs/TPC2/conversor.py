import re
import sys

# Ler o conteúdo do arquivo .md
with open("exemplo.md", "r", encoding="utf-8") as file:
    markdown_content = file.read()


def process_line(line):
    # Converter os cabeçalhos
    c1 = re.compile("^(\#) (.*)")
    c2 = re.compile("^(\#\#) (.*)")
    c3 = re.compile("^(\#\#\#) (.*)")
    c4 = re.compile("^(\#\#\#\#) (.*)")
    c5 = re.compile("^(\#\#\#\#\#) (.*)")
    c6 = re.compile("^(\#\#\#\#\#\#) (.*)")
    # Converter os links
    link = re.compile("^\[(.*)]\((.*)\) - (.+)")
    # Converter as imagens
    i1 = re.compile("!\[((.+))\]\(((.+))\) - (.+)")
    # Converter bolds
    b1 = re.compile("(\*\*)(.*)(\*\*)")
    # Converter itálico
    italico = re.compile("(\*)(.*)(\*)")
    # Converter listas numeradas
    lis = re.compile("^[0-9]+\. (.+)")

    line = re.sub(c1,r'<h1>\2</h1>', line)
    line = re.sub(c2,r'<h2>\2</h2>', line)
    line = re.sub(c3,r'<h3>\2</h3>', line)
    line = re.sub(c4,r'<h4>\2</h4>', line)
    line = re.sub(c5,r'<h5>\2</h5>', line)
    line = re.sub(c6,r'<h6>\2</h6>', line)
    line = re.sub(link,r'<a href="\2">\1</a>', line)
    line = re.sub(i1,r'<img src="\2" alt="\1"/>', line)
    line = re.sub(b1,r'<b>\2</b>', line)
    line = re.sub(italico,r'<i>\2</i>', line)
    line = re.sub(lis, r'<li>\1</li>', line)
    return line



def convertelistas(listas):
    resultado = "<ol>\n"
    for item in listas:
        resultado += f"     <li>{item}</li>\n"
    resultado += "</ol>"
    return resultado

if len(sys.argv) == 3:
    lines = []
    listas = []
    with open(sys.argv[1]) as in_file: 
        for line in in_file:
            # Guardar as linhas do ficheiro numa lista
            lines.append(line)
            
    with open(sys.argv[2], "w") as output_file:
        output_file.write("<html>\n")
        i = 0  # Initialize the index
        j = 0
        while i < len(lines):
            line = process_line(lines[i]) 
            match_list = re.findall("^[0-9]+\. (.+)", lines[i])
            if match_list:
                listas.append(match_list[0])
            else:
                # Ver se já não é uma linha de lista
                if listas:
                    print(listas)
                    output_file.write(convertelistas(listas))
                    listas = []  # Limpar a lista para o próximo conjunto de itens
                else:
                    output_file.write(line)
            i += 1
            
        # Verificar se há itens restantes na lista no final do arquivo
        if listas:
            output_file.write(convertelistas(listas))
        output_file.write("\n</html>")
