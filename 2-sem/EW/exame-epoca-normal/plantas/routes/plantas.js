var express = require('express');
var router = express.Router();
var Planta = require ("../controllers/planta")

router.get('/', async (req, res) => {
  if(req.query.especie) {
    Planta.getEspecie(req.query.especie)
      .then(data => res.jsonp(data))
      .catch(erro => res.jsonp(erro));
  }
  if(req.query.implant) {
    Planta.getImplant(req.query.implant)
  .then(data => res.jsonp(data))
  .catch(erro => res.jsonp(erro))
  }
  else {
    Planta.list()
    .then(data => res.jsonp(data))
    .catch(erro => res.jsonp(erro))
  }
});

router.get('/freguesias', async (req, res) => {
  console.log("ok")
    Planta.distinct1() 
    .then(data => res.jsonp(data))
    .catch(erro => res.jsonp(erro))
});

router.get('/especies', async (req, res) => {
    Planta.distinct2()   
    .then(data => res.jsonp(data))
    .catch(erro => res.jsonp(erro))
});

router.get('/:id', async (req, res) => {
  Planta.findById(req.params.id)
  .then(data => res.jsonp(data))
  .catch(erro => res.jsonp(erro))
});

router.post('/', async (req, res) => {
    Planta.insert(req.body)
    .then(data => res.status(201).jsonp(data))
    .catch(erro => res.status(523).jsonp(erro))
});

router.put('/:id', function(req, res) {
  Planta.update(req.params.id, req.body)
    .then(data => res.status(202).jsonp(data))
    .catch(erro => res.status(524).jsonp(erro))
});

router.delete('/:id', function(req, res) {
  const plantaId = req.params.id;
  Planta.delete(plantaId)
      .then(data => res.status(203).end())
      .catch(erro => res.status(525).jsonp(erro))
});

module.exports = router;
