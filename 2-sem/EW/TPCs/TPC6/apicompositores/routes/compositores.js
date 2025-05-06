var express = require('express');
var router = express.Router();
var Compositor = require ("../controllers/compositor");

/* GET home page. */
router.get('/', function(req, res) {
  Compositor.list()
  .then(compositores =>{
    var d = new Date().toISOString().substring(0, 16)
    res.status(200).render("compositoresListPage", {'lCompositores' : compositores, 'date' : d})
  })
  .catch(erro =>{
      res.status(501).render('error', {'error' : erro})
  })
});

router.get('/registo', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  res.status(200).render("compositoresFormPage", {'date' : d})
});

router.get('/:id', function(req, res) {
  Compositor.findById(req.params.id)
  .then(compositor =>{
    var d = new Date().toISOString().substring(0, 16)
    res.status(200).render("compositorPage", {'compositor' : compositor, 'date' : d})
  })
  .catch(erro =>{
      res.status(503).render('error', {'error' : erro})
  })
});

router.get('/edit/:id', function(req, res, next) {
  Compositor.findById(req.params.id)
  .then(compositor =>{
    var d = new Date().toISOString().substring(0, 16)
    res.status(200).render("compositorEditPage", {'compositor' : compositor, 'date' : d})
  })
  .catch(erro =>{
    res.status(504).render('error', {'error' : erro})
  })
});

router.post('/registo', function(req, res, next) {
  console.log(req.body)
  Compositor.insert(req.body)
  .then(resp => {
      res.redirect("/")
  })
  .catch(erro => {
    res.status(502).render('error', {'error' : erro})
  })
});

router.post('/edit/:id', function(req, res) {
  console.log(req.body);
  Compositor.update(req.params.id, req.body)
  .then(resp =>{
      res.redirect("/")
  })
  .catch(erro =>{
      res.status(505).render('error', {'error' : erro})
  })
});

router.get('/delete/:id', function(req, res, next) {
  Compositor.delete(req.params.id)
  .then(compositor =>{
      res.redirect("/")
  })
  .catch(erro =>{
      res.status(506).render('error', {'error' : erro})
  })
});

module.exports = router;

