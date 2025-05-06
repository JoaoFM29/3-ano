var express = require('express');
var router = express.Router();
var axios = require('axios')

// periodos
/* GET lista periodos . */
router.get('/', function(req, res, next) { 
    var d = new Date().toISOString().substring(0, 16)
    axios.get("http://localhost:3000/periodos?_sort=nome")
    .then(resp =>{
        periodos = resp.data
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
  
  router.get('/:idPeriodo', function(req, res, next) {
    var d = new Date().toISOString().substring(0, 16)
    var idPeriodo = req.params.idPeriodo
    axios.get("http://localhost:3000/periodos/" + idPeriodo)
    .then(resp =>{
        periodo = resp.data
        res.status(200).render("periodoPage", {'periodo' : periodo, 'date' : d})
    })
    .catch(erro =>{
        res.status(503).render('error', {'error' : erro})
    })
  });
  
  router.get('/edit/:idPeriodo', function(req, res, next) {
    var d = new Date().toISOString().substring(0, 16)
    var idPeriodo = req.params.idPeriodo
    axios.get("http://localhost:3000/periodos/" +idPeriodo)
    .then(resp =>{
        periodo = resp.data
        res.status(200).render("periodoEditPage", {'periodo' : periodo, 'date' : d})
    })
    .catch(erro =>{
        res.status(504).render('error', {'error' : erro})
    })
  });
  
  router.post('/registo', function(req, res, next) {
    var d = new Date().toISOString().substring(0, 16)
    result = req.body
    axios.post("http://localhost:3000/periodos", result)
    .then(resp => {
        res.redirect("/")
    })
    .catch(erro => {
      res.status(502).render('error', {'error' : erro})
    })
  });
  
  router.post('/edit/:nomePeriodo', function(req, res, next) {
    var d = new Date().toISOString().substring(0, 16)
    var periodo = req.body
    axios.put("http://localhost:3000/periodos/" + periodo.nome, periodo)
    .then(resp =>{
        res.redirect("/")
    })
    .catch(erro =>{
        res.status(505).render('error', {'error' : erro})
    })
  });
  
  router.get('/delete/:nomePeriodo', function(req, res, next) {
    var d = new Date().toISOString().substring(0, 16)
    var id = req.params.nomePeriodo
    axios.delete("http://localhost:3000/periodos/" + nome)
    .then(resp =>{
        res.redirect("/")
    })
    .catch(erro =>{
        res.status(506).render('error', {'error' : erro})
    })
  });
  
  module.exports = router;
  

module.exports = router;
