caminho_arquivo = '/Users/jony/Documents/GitHub/PL2024/TP1/emd.csv'

# Abrir o ficheiro csv
with open(caminho_arquivo, 'r') as ficheiro:
    next(ficheiro) # a primeira linha é cabeçalho
    modalidades = set()
    counterA = 0
    counterIA = 0
    percentagemA = 0
    percentagemIA = 0
    idades = []
    atletas1 = []
    atletas2 = []
    atletas3 = []
    
    for linha in ficheiro:
        campos = linha.split(',')
        
        modalidades.add(campos[8])
        
        if campos[12].strip().lower() == "true":
            counterA += 1
        else:
            counterIA += 1
            
        idade = campos[5]
        idades.append(idade)
        
        intIdade = int(idade)
        primeiroNome = campos[3]
        ultimoNome = campos[4]
    
        if intIdade >= 21 and intIdade <= 25:
            atletas1.append((primeiroNome,ultimoNome))
        elif intIdade >= 26 and intIdade <= 30:
            atletas2.append((primeiroNome,ultimoNome))
        elif intIdade >= 31 and intIdade <= 35:
            atletas3.append((primeiroNome,ultimoNome))
        
        
    idadeMin = min(idades)
    modalidadesL = list(modalidades)
    modalidadesL.sort()
    percentagemA = counterA / (counterA + counterIA) * 100
    percentagemIA = counterIA / (counterA + counterIA) * 100


def imprimir_resultados(modalidades_lista, percentagemA, percentagemIA, atletas1, atletas2, atletas3):
    print("\nLista ordenada alfabeticamente das modalidades desportivas")
    print(modalidades_lista)

    print("\nPercentagens de atletas aptos e inaptos para a prática desportiva")
    print("Aptos: ", percentagemA,"%")
    print("Inaptos: ", percentagemIA,"%\n")

    print("Distribuição de atletas por escalão etário (escalão = intervalo de 5 anos): ... [30-34], [35-39], ...")
    print("Dado que a idade minima é 21 os intrevalos serão [21-25], [26-30], [31-35]")
    print("Atletas entre [21-25]\n", atletas1)
    print("Atletas entre [26-30]\n", atletas2)
    print("Atletas entre [31-35]\n", atletas3)
    

imprimir_resultados(modalidades, percentagemA, percentagemIA, atletas1, atletas2, atletas3)
