var express = require('express');
var router = express.Router();
var Pessoa = require ("../controllers/pessoa")

/* GET home page. */
router.get('/', function(req, res) {
  Pessoa.list()
  .then(data => res.jsonp(data))
  .catch(erro => res.jsonp(erro))
});
router.get('/:id', function(req, res) {
  Pessoa.findById(req.params.id)
  .then(data => res.jsonp(data))
  .catch(erro => res.jsonp(erro))
});

// Rota para obter a lista de modalidades
router.get('/modalidades', (req, res) => {
  Pessoa.getModalidades ()
  .then(data => res.jsonp(data))
  .catch(erro => res.jsonp(erro))
});

// Rota para obter a lista de modalidades
router.get('/modalidades/:modalidade', (req, res) => {
  Pessoa.getPessoasModal (req.params.modalidade)
  .then(data => res.jsonp(data))
  .catch(erro => res.jsonp(erro))
});

router.post('/', function(req, res) {
  Pessoa.insert(req.body)
    .then(data => res.status(201).jsonp(data))
    .catch(erro => res.status(523).jsonp(erro))
});

router.put('/:id', function(req, res) {
  Pessoa.update(req.params.id, req.body)
    .then(data => res.status(202).jsonp(data))
    .catch(erro => res.status(524).jsonp(erro))
});

router.delete('/:id', function(req, res) {
  const pessoaId = req.params.id;
  Pessoa.delete(pessoaId)
      .then(data => res.status(203).end())
      .catch(erro => res.status(525).jsonp(erro))
});

module.exports = router;



