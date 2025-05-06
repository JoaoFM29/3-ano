const express = require('express');
const axios = require('axios');

const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.static('public'));
app.use(express.json());

// Rota para renderizar a página HTML com a tabela e botões
app.get('/', (req, res) => {
  res.sendFile(__dirname + '/public/index.html');
});

// Rota para obter e enviar dados da API externa para a página HTML
app.get('/api/pessoas', async (req, res) => {
  try {
    const response = await axios.get('http://localhost:7777/pessoas');
    res.json(response.data);
  } catch (error) {
    res.status(500).send('Erro ao obter dados da API externa');
  }
});

// Rota para deletar uma pessoa na API externa
app.delete('/api/pessoas/:id', async (req, res) => {
  const { id } = req.params;
  try {
    await axios.delete(`http://localhost:7777/pessoas/${id}`);
    res.status(204).end();
  } catch (error) {
    res.status(500).send('Erro ao deletar pessoa na API externa');
  }
});

// Rota para atualizar uma pessoa na API externa
app.put('/api/pessoas/:id', async (req, res) => {
    const { id } = req.params;
    const updatedPerson = req.body; // Os dados atualizados são recebidos no corpo da requisição
    try {
      await axios.put(`http://localhost:7777/pessoas/${id}`, updatedPerson);
      res.status(200).send('Pessoa atualizada com sucesso na API externa');
    } catch (error) {
      res.status(500).send('Erro ao atualizar pessoa na API externa');
    }
  });
  
  // Rota para obter uma pessoa por ID na API externa
  app.get('/api/pessoas/:id', async (req, res) => {
    const { id } = req.params;
    try {
      const response = await axios.get(`http://localhost:7777/pessoas/${id}`);
      res.json(response.data);
    } catch (error) {
      if (error.response.status === 404) {
        res.status(404).send('Pessoa não encontrada na API externa');
      } else {
        res.status(500).send('Erro ao obter pessoa da API externa');
      }
    }
  });

app.listen(PORT, () => {
  console.log(`Servidor rodando na porta ${PORT}`);
});
