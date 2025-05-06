const express = require('express');
const router = express.Router();
const Pessoa = require('../models/pessoa');

// Rota para listar todas as pessoas
router.get('/pessoas', (req, res) => {
    Pessoa.find()
        .then(people => res.json(people))
        .catch(err => res.status(500).json({ error: 'Erro ao buscar pessoas' }));
});

// Rota para obter uma pessoa por ID
router.get('/pessoas/:id', (req, res) => {
    const id = req.params.id;
    Pessoa.findById(id)
        .then(person => {
            if (!person) {
                return res.status(404).json({ error: 'Pessoa não encontrada' });
            }
            res.json(person);
        })
        .catch(err => res.status(500).json({ error: 'Erro ao buscar pessoa por ID' }));
});

// Rota para adicionar uma nova pessoa
router.post('/pessoas', (req, res) => {
    const newPerson = req.body;
    Pessoa.create(newPerson)
        .then(person => res.status(201).json(person))
        .catch(err => res.status(500).json({ error: 'Erro ao adicionar pessoa' }));
});

// Rota para atualizar uma pessoa por ID
router.put('/pessoas/:id', (req, res) => {
    const id = req.params.id;
    const updatedPerson = req.body;
    Pessoa.findByIdAndUpdate(id, updatedPerson, { new: true })
        .then(person => {
            if (!person) {
                return res.status(404).json({ error: 'Pessoa não encontrada para atualização' });
            }
            res.json(person);
        })
        .catch(err => res.status(500).json({ error: 'Erro ao atualizar pessoa por ID' }));
});

// Rota para deletar uma pessoa por ID
router.delete('/pessoas/:id', (req, res) => {
    const id = req.params.id;
    Pessoa.findByIdAndDelete(id)
        .then(person => {
            if (!person) {
                return res.status(404).json({ error: 'Pessoa não encontrada para exclusão' });
            }
            res.json({ message: 'Pessoa excluída com sucesso' });
        })
        .catch(err => res.status(500).json({ error: 'Erro ao deletar pessoa por ID' }));
});

module.exports = router;

