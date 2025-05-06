/* Operações CRUD sobre Entrega 
  2024-04-21 @jcr
   ----------------------- */
var express = require('express');
var router = express.Router();
var Entrega = require('../controllers/entrega')
var EntregaRemovida = require('../controllers/entregaRemovida');
var multer = require('multer')
var fs = require('fs');

var Auth = require('../auth/auth')

var uploads = multer({ dest : './uploads' })

/* Listar as Entrega (R) */
router.get('/', function(req, res) {
  if(req.query.projeto){
    Entrega.findByProjeto(req.query.projeto)
        .then(data => res.jsonp(data))
        .catch(erro => res.jsonp(erro))
  }else{
    Entrega.list()
        .then(data => res.jsonp(data))
        .catch(erro => res.jsonp(erro))
  }
});

/* Consultar uma Entrega (R) */
router.get('/:id', function(req, res) {
    Entrega.findById(req.params.id)
      .then(data => res.jsonp(data))
      .catch(erro => res.jsonp(erro))
  });

/* Criar uma Entrega (C) */
router.post('/', Auth.verificaAcesso ,uploads.single('ficheiro'), function(req, res) { // TODO
  const entrega = {
    _id : req.body._id,
    creationDate : new Date(),
    uc : req.body.uc,
    idProj : req.body.idProj,
    designacaoProj : req.body.designacaoProj,
    designacaoEq : req.body.designacaoEq,
    idEq : req.body.idEq,
    ficheiro : req.file.originalname,
    obs: req.body.obs
  };
  Entrega.insert(entrega) 
  .then(data => {
    fs.mkdir( __dirname + "/../FileStore/" + entrega._id, { recursive: true }, (err) => {
      if (err) {
        console.error('Error creating folder:', err);
      } else {
        console.log('Folder created successfully: ' + entrega._id);
          let oldPath = __dirname + '/../' + req.file.path 
          let newPath = __dirname + '/../FileStore/' + entrega._id + '/' + req.file.originalname

          fs.rename(oldPath, newPath, function(error){
            if(error) throw error
          })
      }
    });
    res.status(201).jsonp(data)
  })
  .catch(erro => res.jsonp(erro))
});

/* Alterar uma Entrega (U) */
router.put('/:id', function(req, res) {
    Entrega.update(req.params.id, req.body)
      .then(data => res.jsonp(data))
      .catch(erro => res.jsonp(erro))
  });

/* Remover uma Entrega (D ) */
router.delete('/:id', function(req, res) {
    Entrega.remove(req.params.id)
      .then(entrega => {
        var entregaRemovida = {
          //_id : req.params.id,
          removeDate : new Date(),
          uc : entrega.uc,
          idProj : entrega.idProj,
          designacaoProj : entrega.designacaoProj,
          designacaoEq : entrega.designacaoEq,
          idEq : entrega.idEq,
          ficheiro : entrega.ficheiro,
          obs : entrega.obs,
          justificacao : req.body.justificacao
        }
        fs.rmdirSync(__dirname + '/../FileStore/' + req.params.id, { recursive : true, force : true})
        EntregaRemovida.insert(entregaRemovida)
          .then(data => {
            console.log("Deleted " + req.params.id)
            res.jsonp(data)
        })
          .catch(erro => res.jsonp(erro))

        // remover pasta
        
      })
      .catch(erro => res.jsonp(erro))
  });

module.exports = router;
