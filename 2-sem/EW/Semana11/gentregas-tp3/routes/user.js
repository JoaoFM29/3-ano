var express = require('express');
var router = express.Router();
var jwt = require('jsonwebtoken')
var passport = require('passport')
var userModel = require('../models/user')

var User = require('../controllers/user')

router.get('/', function(req, res){
  User.list()
    .then(dados => res.status(200).jsonp({dados: dados}))
    .catch(e => res.status(500).jsonp({error: e}))
})

router.get('/:id', function(req, res){
  User.getUser(req.params.id)
    .then(dados => res.status(200).jsonp({dados: dados}))
    .catch(e => res.status(500).jsonp({error: e}))
})

router.post('/', function(req, res){
  User.addUser(req.body)
    .then(dados => res.status(201).jsonp({dados: dados}))
    .catch(e => res.status(500).jsonp({error: e}))
})

router.post('/register', function(req, res) {
  var d = new Date().toISOString().substring(0,19)
  userModel.register(new userModel({ username: req.body.username, name: req.body.name, 
                                      level: req.body.level, active: true, dateCreated: d }), 
    req.body.password, 
    function(err, user) {
      if (err) 
        res.jsonp({error: err, message: "Register error: " + err})
      else{
        passport.authenticate("local")(req,res,function(){
          jwt.sign({ username: req.user.username, level: req.user.level, 
            sub: 'aula de EngWeb2024'}, 
            "ew2024",
            {expiresIn: 3600},
            function(e, token) {
              if(e) res.status(500).jsonp({error: "Erro na geração do token: " + e}) 
              else res.status(201).jsonp({token: token})
            });
        })
      }     
  })
})
  
router.post('/login', passport.authenticate('local'), function(req, res){
  jwt.sign({ username: req.body.username}, 
    "ew2024",
    {expiresIn: 3600},
    function(e, token) {
      if(e) res.status(500).jsonp({error: "Erro na geração do token: " + e}) 
      else res.status(201).jsonp({token: token})
});
})

router.put('/:id', function(req, res) {
  User.updateUser(req.params.id, req.body)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na alteração do utilizador"})
    })
})

router.put('/:id/desativar', function(req, res) {
  User.updateUserStatus(req.params.id, false)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na alteração do utilizador"})
    })
})

router.put('/:id/ativar', function(req, res) {
  User.updateUserStatus(req.params.id, true)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na alteração do utilizador"})
    })
})

router.put('/:id/password',  function(req, res) {
  User.updateUserPassword(req.params.id, req.body)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na alteração do utilizador"})
    })
})

router.delete('/:id', function(req, res) {
  User.deleteUser(req.params.id)
    .then(dados => {
      res.jsonp(dados)
    })
    .catch(erro => {
      res.render('error', {error: erro, message: "Erro na remoção do utilizador"})
    })
})

module.exports = router;