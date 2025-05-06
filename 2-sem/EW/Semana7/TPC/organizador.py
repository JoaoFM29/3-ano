import json
from datetime import datetime, timedelta
import random

def calcular_periodo_nascimento(compositor):
    if "dataNasc" in compositor:
        data_nascimento = datetime.strptime(compositor["dataNasc"], "%Y-%m-%d")
        
        if data_nascimento.year < 1700:
            return "Renascimento"
        elif data_nascimento.year < 1750:
            return "Barroco"
        elif data_nascimento.year < 1820:
            return "Clássico"
        elif data_nascimento.year < 1900:
            return "Romântico"
        else:
            return "Contemporâneo"
    else:
        return "Desconhecido"

def criar_data_baseado_no_periodo(periodo):
    # Definir datas de início para cada período musical
    inicio_renascimento = datetime(1400, 1, 1)
    inicio_barroco = datetime(1600, 1, 1)
    inicio_classico = datetime(1730, 1, 1)
    inicio_romantico = datetime(1800, 1, 1)
    inicio_contemporaneo = datetime(1900, 1, 1)
    
    # Mapear o período para a data de início correspondente
    inicio_por_periodo = {
        "Renascimento": inicio_renascimento,
        "Barroco": inicio_barroco,
        "Clássico": inicio_classico,
        "Romântico": inicio_romantico,
        "Contemporâneo": inicio_contemporaneo
    }

    # Obter a data de início correspondente ao período
    inicio_periodo = inicio_por_periodo.get(periodo, datetime(1400, 1, 1))

    # Criar uma data de nascimento com base no período
    nova_data_nascimento = inicio_periodo + timedelta(days=random.randint(365, 365 * 50))  # Adiciona 1 a 50 anos à data de início como exemplo

    return nova_data_nascimento.strftime("%Y-%m-%d")

def validar_compositor(compositor):
    campos_obrigatorios = ["id", "nome", "bio", "dataNasc", "dataObito", "periodo"]
    
    for campo in campos_obrigatorios:
        if campo not in compositor:
            return False
    
    # Verifica se a chave "dataNasc" está presente no dicionário
    if "dataNasc" in compositor:
        try:
            # Tenta converter a data para verificar se está no formato correto
            datetime.strptime(compositor["dataNasc"], "%Y-%m-%d")
        except ValueError:
            # Em caso de erro, corrige o formato acrescentando o ano que tem e definindo o mês e o dia para 1
            compositor["dataNasc"] = f"{compositor['dataNasc'][:4]}-01-01"
    
    # Verifica se a chave "dataObito" está presente no dicionário
    if "dataObito" in compositor:
        try:
            # Tenta converter a data para verificar se está no formato correto
            datetime.strptime(compositor["dataObito"], "%Y-%m-%d")
        except ValueError:
            # Em caso de erro, corrige o formato acrescentando o ano que tem e definindo o mês e o dia para 1
            compositor["dataObito"] = f"{compositor['dataObito'][:4]}-01-01"

    return True

def organizar_compositores_por_periodo(compositores):
    periodos_musicais = {}
    
    for compositor in compositores:
        periodo_nascimento = calcular_periodo_nascimento(compositor)
        
        # Verifica se o período já foi adicionado
        if periodo_nascimento not in periodos_musicais:
            periodos_musicais[periodo_nascimento] = {"id": len(periodos_musicais), "nome": periodo_nascimento}
    
    return list(periodos_musicais.values())


def corrigir_dataset(dataset):
    # Remove entradas com atributos fora do esperado
    compositores_validos = [c for c in dataset["compositores"] if validar_compositor(c)]
    
    # Adiciona entrada fictícia para cada compositor inválido
    compositores_invalidos = [c for c in dataset["compositores"] if not validar_compositor(c)]
    for compositor_invalido in compositores_invalidos:
        periodo_nascimento = calcular_periodo_nascimento(compositor_invalido)
        compositor_invalido["dataNasc"] = criar_data_baseado_no_periodo(periodo_nascimento)
        compositor_invalido["dataObito"] = "1400-01-01"
        compositor_invalido["periodo"] = "Desconhecido"
        compositor_invalido["nome"] = "Desconhecido"
        compositor_invalido["bio"] = "Informação biográfica não disponível."
    
    # Organiza os compositores por período
    compositores_por_periodo = organizar_compositores_por_periodo(compositores_validos)
    
    return compositores_validos,compositores_por_periodo
    
with open('compositores.json', 'r', encoding='utf-8') as file:
    entrada_json = file.read()
    
dataset_json = json.loads(entrada_json)
dataset_corrigido = corrigir_dataset(dataset_json)

json_resultado = json.dumps(dataset_corrigido, indent=2, ensure_ascii=False)

# Correção na escrita para 'write' em vez de 'dump'
with open('compositoresValido.json', 'w', encoding="utf-8") as file:
    texto_sem_virgulas = json_resultado.replace('},', '}').replace(',{', '{')
    texto_sem_braquetes = texto_sem_virgulas.replace('[', '').replace('],', '').replace(']', '')
    texto_id = texto_sem_braquetes.replace('id', '_id')
        
    file.write(texto_id)