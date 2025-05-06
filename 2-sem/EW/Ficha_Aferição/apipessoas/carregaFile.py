import json
import requests

# Função para ler dados de um arquivo JSON
def read_json_file(file_path):
    try:
        with open(file_path, 'r') as file:
            data = json.load(file)
            return data
    except Exception as e:
        raise Exception(f"Erro ao ler arquivo JSON: {str(e)}")

# Função para enviar dados para a API via requisição POST
def send_data_to_api(api_url, data):
    try:
        response = requests.post(api_url, json=data)
        response.raise_for_status()  # Lança uma exceção se houver erro na requisição
    except requests.exceptions.RequestException as e:
        raise Exception(f"Erro ao enviar dados para a API: {str(e)}")

# Caminho para o arquivo JSON com os dados a serem carregados
json_file_path = '../datasets/dataset_com_ids-extra3.json'

# URL da sua API
api_base_url = 'http://localhost:7777/pessoas'

# Função principal para carregar dados do JSON para a API
def main():
    try:
        # Ler dados do arquivo JSON
        json_data = read_json_file(json_file_path)

        # Enviar cada entrada para a API
        for entry in json_data:
            send_data_to_api(api_base_url, entry)

        print('Todos os dados foram enviados com sucesso para a base de dados.')
    except Exception as e:
        print(f'Erro ao carregar dados para a API: {str(e)}')

# Chamar a função principal para iniciar o processo de carga de dados
if __name__ == "__main__":
    main()
