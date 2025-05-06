import json

# Função para adicionar IDs
def adicionar_ids(dados):
    idx = 14001  # Definir o valor inicial do ID
    pessoas = dados["pessoas"]
    for pessoa in pessoas:
        pessoa["_id"] = idx   # Atribuir o ID atual
        idx += 1  # Incrementar para o próximo ID
    return dados

# Carregar dados do arquivo JSON
def carregar_dados_do_arquivo(nome_arquivo):
    with open(nome_arquivo, 'r', encoding='utf-8') as arquivo:
        dados = json.load(arquivo)
    return dados

# Salvar dados em um arquivo JSON
def salvar_dados_no_arquivo(dados, nome_arquivo):
    with open(nome_arquivo, 'w', encoding='utf-8') as arquivo:
        json.dump(dados, arquivo, ensure_ascii=False, indent=4)

# Nome dos arquivos de entrada e saída
nome_arquivo_entrada = 'dataset-extra3.json'
nome_arquivo_saida = 'dataset_com_ids-extra3.json'

# Carregar dados do arquivo JSON de entrada
dados_originais = carregar_dados_do_arquivo(nome_arquivo_entrada)

# Adicionar IDs aos dados
dados_com_ids = adicionar_ids(dados_originais)

# Salvar os dados com IDs em um novo arquivo JSON
salvar_dados_no_arquivo(dados_com_ids, nome_arquivo_saida)