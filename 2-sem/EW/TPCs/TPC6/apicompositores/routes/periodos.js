var express = require('express');
var router = express.Router();
var Periodo = require ("../controllers/periodo");

/* GET lista periodos . */
router.get('/', function(req, res) { 
    Periodo.list()
    .then(periodos =>{
      var d = new Date().toISOString().substring(0, 16)
        res.status(200).render("periodosListPage", {'lPeriodos' : periodos, 'date' : d})
    })
    .catch(erro =>{
        res.status(501).render('error', {'error' : erro})
    })
  });

  router.get('/registo', function(req, res, next) {
    var d = new Date().toISOString().substring(0, 16)
    res.status(200).render("periodosFormPage", {'date' : d})
  });

  router.get('/:id', function(req, res, next) {
    Periodo.findById(req.params.id)
    .then(periodo =>{
        var d = new Date().toISOString().substring(0, 16)
        res.status(200).render("periodoPage", {'periodo' : periodo, 'date' : d})
    })
    .catch(erro =>{
        res.status(503).render('error', {'error' : erro})
    })
  });

  router.get('/edit/:id', function(req, res, next) {
    Periodo.findById(req.params.id)
    .then(periodo =>{
      console.log(periodo)
      var d = new Date().toISOString().substring(0, 16)
      res.status(200).render("periodoEditPage", {'periodo' : periodo, 'date' : d})
    })
    .catch(erro =>{
      res.status(504).render('error', {'error' : erro})
    })
  });
  
  router.post('/registo', function(req, res) {
    console.log(req.body)
    Periodo.insert(req.body)
    .then(resp => {
      res.redirect("/")
    })
    .catch(erro => {
      res.status(502).render('error', {'error' : erro})
    })
  });

  router.post('/edit/:id', function(req, res) {
    console.log(req.body);
    Periodo.update(req.params.id, req.body)
    .then(resp =>{
        res.redirect("/")
    })
    .catch(erro =>{
        res.status(505).render('error', {'error' : erro})
    })
  });

  router.get('/delete/:id', function(req, res, next) {
    Periodo.delete(req.params.id)
    .then(periodo =>{
        res.redirect("/")
    })
    .catch(erro =>{
        res.status(506).render('error', {'error' : erro})
    })
  });
  
module.exports = router;

