import csv

def pot_recursiva(b, e):
    if e == 0:
        return 1
    return b * pot_recursiva(b, e - 1)


def pot_iterativa(b, e):
    resultado = 1
    for i in range(1, e + 1):
        resultado *= b
    return resultado


base = int(input("Base: "))
einf = int(input("Expoente inferior: "))
esup = int(input("Expoente superior: "))

for e in range(einf, esup + 1):
    print(str(base) + "^" + str(e) + " = " + str(pot_recursiva(base, e)))


def unzip(l):
    l1 = []
    l2 = []
    for um, dois in l:
        l1.append(um)
        l2.append(dois)
    return l1, l2


lista = [(1, "banana"), (2, "maçã"), (3, "melancia"), (4, "cereja")]

(unzipped1, unzipped2) = unzip(lista)

print(unzipped1)
print(unzipped2)


def count_lines_in_csv():
    with open('alunos.csv', mode='r') as file:
        reader = csv.reader(file)

        # Count the number of rows
        num_lines = sum(1 for row in reader)
        return num_lines


print(f"Number of lines : {count_lines_in_csv()}")

alunos_dict = {}


def adicionar_aluno(id_aluno, nome, curso, notas):
    alunos_dict[id_aluno] = {'nome': nome,
                             'curso': curso,
                             'notas': {'TPC1': notas[0], 'TPC2': notas[1], 'TPC3': notas[2], 'TPC4': notas[3]}
                             }


def openFile():
    with open('alunos.csv', mode='r') as file:
        reader = csv.reader(file)
        next(reader)  # Pular cabeçalhos

        for row in reader:
            id_aluno = row[0]
            nome = row[1]
            curso = row[2]
            notas = [row[i] for i in range(3, 7)]
            adicionar_aluno(id_aluno, nome, curso, notas)

openFile()

nomeAlunos_dict = {}
def adicionar_NomeNota(x, nome, nota):
    nomeAlunos_dict[x] = {'nome': nome, 'media': nota}

def ordenaNotas():
    x = 0
    counter = 0

    for chave, valor in alunos_dict.items():
        nome_aluno = valor['nome']
        media_aluno = 0
        for tpc, nota in valor['notas'].items():
            media_aluno += int(nota)
            x += 1
        media_aluno = media_aluno/x
        x=0
        adicionar_NomeNota(counter, nome_aluno, media_aluno)
        counter += 1
    nomeAlunos_ordenado = sorted(nomeAlunos_dict.items(), key=lambda item: item[1]['media'], reverse=True)
    return nomeAlunos_ordenado

def contaSup15(nomeAlunos_ordenado):
    contaAlunos = 0
    for key, value in nomeAlunos_ordenado:
        if value['media'] > 15:
            contaAlunos += 1
    return contaAlunos

print(contaSup15(ordenaNotas()))
