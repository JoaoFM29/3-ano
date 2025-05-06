var express = require('express');
var router = express.Router();
var Contrato = require ("../controllers/contrato")

router.get('/', async (req, res) => {
  if(req.query.entidade) {
    console.log(req.query.entidade)
    Contrato.getEntidade(req.query.entidade)
      .then(data => res.jsonp(data))
      .catch(erro => res.jsonp(erro));
  }
  else if(req.query.tipo) {
    Contrato.getTipo(req.query.tipo)
    .then(data => res.jsonp(data))
    .catch(erro => res.jsonp(erro))
  }
  else {
    Contrato.list()
    .then(data => res.jsonp(data))
    .catch(erro => res.jsonp(erro))
  }
});

router.get('/entidades', async (req, res) => {
    Contrato.list2()
    .then(data => res.jsonp(data))
    .catch(erro => res.jsonp(erro))
  
});

router.get('/tipos', async (req, res) => {
  Contrato.list3()
  .then(data => res.jsonp(data))
  .catch(erro => res.jsonp(erro))
});

router.get('/:id', async (req, res) => {
  Contrato.findById(req.params.id)
  .then(data => res.jsonp(data))
  .catch(erro => res.jsonp(erro))
});

router.post('/', async (req, res) => {
    Contrato.insert(req.body)
    .then(data => res.status(201).jsonp(data))
    .catch(erro => res.status(523).jsonp(erro))
});

router.put('/:id', function(req, res) {
  Contrato.update(req.params.id, req.body)
    .then(data => res.status(202).jsonp(data))
    .catch(erro => res.status(524).jsonp(erro))
});

router.delete('/:id', function(req, res) {
  const contratoId = req.params.id;
  Contrato.delete(contratoId)
      .then(data => res.status(203).end())
      .catch(erro => res.status(525).jsonp(erro))
});

module.exports = router;
