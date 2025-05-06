var express = require('express');
var router = express.Router();
var axios = require('axios')


/* GET list alunos. */
router.get('/', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  axios.get("http://jserver:3000/alunos?_sort=nome")
    .then(response => {
      var alunos = response.data
      res.status(200).render('studentsListPage', {"slist" : alunos, "d" : d})
    })
    .catch(erro => {
      res.status(500).render('error', {"error" : erro})
    })
});

/* GET registo */
router.get('/registo', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  res.status(200).render('studentFormPage', {"d" : d})
});

/* GET aluno */
router.get('/:idAluno', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  axios.get("http://jserver:3000/alunos/" + req.params.idAluno)
    .then(response => {
      var aluno = response.data
      res.status(200).render('studentPage', {"aluno" : aluno, "d" : d})
    })
    .catch(erro => {
      res.status(501).render('error', {"error" : erro})
    })
});


/* GET aluno */
router.get('/edit/:idAluno', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  axios.get('http://jserver:3000/alunos/' + req.params.idAluno)
  .then(function(resp){
    var aluno = resp.data
    res.status(200).render('studentFormEditPage', {"aluno" : aluno, "d" : d})
  })
  .catch(erro => {
    res.status(506).render('error', {"error" : erro})
  })
});


/* GET aluno */
router.get('/delete/:idAluno', function(req, res, next) {
  axios.delete('http://jserver:3000/alunos/' + req.params.idAluno)
    .then(resp => {
      res.status(200).redirect("/")
    }).catch(error => {
      res.status(504).render('error', {"error" : error})
    })
});



/* POST registo */
router.post('/registo', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  var aluno = req.body
  axios.post('http://jserver:3000/alunos', aluno)
    .then(resp => {
      res.status(201).redirect('/')
    })
    .catch(error => {
      res.status(502).render('error', {"error" : error})
    });

});

/* POST edit aluno */
router.post('/edit/:idAluno', function(req, res, next) {
  var aluno = req.body
  axios.put('http://jserver:3000/alunos/' + aluno.id, aluno)
    .then(resp => {
      res.status(201).redirect('/')
    })
    .catch(error => {
      res.status(505).render('error', {"error" : error})
    });
});


module.exports = router;
  