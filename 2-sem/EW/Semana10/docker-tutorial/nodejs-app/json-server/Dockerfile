# Use a imagem node.js como base
FROM node
# Defina a pasta de trabalho como /app
WORKDIR /app
# Copie a BD para o diretório de trabalho
COPY db.json .
# Instale as dependências
RUN npm install json-server -g
# Exponha a porta 3000
EXPOSE 3000
# Defina o comando padrão a ser executado quando o container for iniciado
CMD ["json-server", "--watch", "db.json", "--port", "3000", "--host", "0.0.0.0"]