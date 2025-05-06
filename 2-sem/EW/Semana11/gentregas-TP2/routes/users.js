var express = require('express');
var router = express.Router();
var jwt = require('jsonwebtoken')
var passport = require('passport')
var userModel = require('../models/user')

var User = require('../controllers/user')


router.post('/register', function(req, res) {
  var d = new Date().toISOString().substring(0,19)
  userModel.register(new userModel({ username: req.body.username, name: req.body.name, 
                                      level: req.body.level, active: true, dateCreated: d }), 
    req.body.password, 
    function(err, user) {
      if (err) 
        res.jsonp({error: err, message: "Register error: " + err})
      else{
        res.send("Success")
      }     
  })
})
  
router.post('/login', passport.authenticate('local'), function(req, res){
  jwt.sign({ username: req.user.username, level: req.user.level, 
    sub: 'aula de EngWeb2024'}, 
    "EngWeb2024",
    {expiresIn: 3600},
    function(e, token) {
      if(e) res.status(500).jsonp({error: "Erro na geração do token: " + e}) 
      else res.status(201).jsonp({token: token})
});
})

router.post('/loginRegister', function(req, res){
  User.getUser(req.body.username)
    .then(data => {
      if(data){ // login
        passport.authenticate('local')
        jwt.sign({ username: req.body.username}, 
          "EngWeb2024",
          {expiresIn: 3600},
          function(e, token) {
            if(e) res.status(500).jsonp({error: "Erro na geração do token: " + e}) 
            else res.status(201).jsonp({token: token})
          });
      }else{  //registo
        var d = new Date().toISOString().substring(0,19)
        userModel.register(new userModel({ username: req.body.username, name: req.body.name, 
                                            level: req.body.level, active: true, dateCreated: d }), 
          req.body.password, 
          function(err, user) {
            if (err) 
              res.jsonp({error: err, message: "Register error: " + err})
            else{
              res.send("Success")
            }     
        })
      }
    })
    .catch(e => res.jsonp(e))
})

module.exports = router;
