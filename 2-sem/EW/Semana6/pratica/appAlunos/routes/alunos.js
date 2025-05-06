var express = require('express');
var router = express.Router();
var axios = require('axios')

/* GET users listing. */
router.get('/', function(req, res, next) { //Já está a responder ao /alunos
  var d = new Date().toISOString().substring(0, 16)
  axios.get("http://localhost:3000/alunos?_sort=nome")
  .then(resp =>{
      alunos = resp.data
      res.status(200).render("studentsListPage", {'lAlunos' : alunos, 'date' : d})
  })
  .catch(erro =>{
      res.status(501).render('error', {'error' : erro})
  })
});

router.get('/registo', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  res.status(200).render("studentsFormPage", {'date' : d})
});

router.post('/registo', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  result = req.body
  axios.post("http://localhost:3000/alunos", result)
  .then(resp => {
      res.redirect("/")
  })
  .catch(erro => {
    res.status(502).render('error', {'error' : erro})
  })
});

router.get('/:idAluno', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  var id = req.params.idAluno
  axios.get("http://localhost:3000/alunos/" +id)
  .then(resp =>{
      aluno = resp.data
      res.status(200).render("studentPage", {'aluno' : aluno, 'date' : d})
  })
  .catch(erro =>{
      res.status(503).render('error', {'error' : erro})
  })
});

router.get('/edit/:idAluno', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  var id = req.params.idAluno
  axios.get("http://localhost:3000/alunos/" +id)
  .then(resp =>{
      aluno = resp.data
      res.status(200).render("studentEditPage", {'aluno' : aluno, 'date' : d})
  })
  .catch(erro =>{
      res.status(504).render('error', {'error' : erro})
  })
});

router.post('/edit/:idAluno', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  var aluno = req.body
  axios.put("http://localhost:3000/alunos/" + aluno.id, aluno)
  .then(resp =>{
      res.redirect("/")
  })
  .catch(erro =>{
      res.status(505).render('error', {'error' : erro})
  })
});

router.get('/delete/:idAluno', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  var id = req.params.idAluno
  axios.delete("http://localhost:3000/alunos/" +id)
  .then(resp =>{
      res.redirect("/")
  })
  .catch(erro =>{
      res.status(506).render('error', {'error' : erro})
  })
});

module.exports = router;
