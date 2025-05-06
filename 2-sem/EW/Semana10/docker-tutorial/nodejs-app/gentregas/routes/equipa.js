/* Operações CRUD sobre UC 
   2024-04-21 @jcr
   ----------------------- */
var express = require('express');
var router = express.Router();
var Equipa = require('../controllers/equipa')
var multer = require('multer')
const upload = multer({ dest: 'uploads/' })
var fs = require('fs')

/* Listar as Equipa (R) */
router.get('/', function(req, res) {
  Equipa.list()
        .then(data => res.jsonp(data))
        .catch(erro => res.jsonp(erro))
});

/* Consultar uma UC (R) */
router.get('/:id', function(req, res) {
  Equipa.findById(req.params.id)
      .then(data => res.jsonp(data))
      .catch(erro => res.jsonp(erro))
  });

/* Criar uma Equipa (C) */
router.post('/', upload.array('foto'), function(req, res) {
  var equipa = {
    _id: req.body._id,
    designacao: req.body.designacao,
    membros:[]
  }
  for( let i=0; i < req.body.membrosId.length; i++){
    equipa.membros.push({
      _id: req.body.membrosId[i],
      nome: req.body.membrosNome[i],
      foto: 'foto' + (i+1)
    })
  }
  Equipa.insert(equipa)
    .then(data => {
      fs.mkdir( __dirname + "/../FileStore/" + equipa._id, { recursive: true }, (err) => {
        if (err) {
          console.error('Error creating folder:', err);
        } else {
          console.log('Folder created successfully: ' + equipa._id);
          for(let i=0; i < req.files.length; i++){
            let oldPath = __dirname + '/../' + req.files[i].path 
            let newPath = __dirname + '/../FileStore/' + equipa._id + '/foto' + (i+1) + '.' + req.files[i].mimetype.split('/')[1] 

            fs.rename(oldPath, newPath, function(error){
              if(error) throw error
            })

          }
        }
      });
      res.status(201).jsonp(data)
    })
    .catch(erro => res.jsonp(erro))
});

/* Alterar uma UC (U) */
router.put('/:id', function(req, res) {
  Equipa.update(req.params.id, req.body)
      .then(data => res.jsonp(data))
      .catch(erro => res.jsonp(erro))
  });

/* Remover uma UC (D ) */
router.delete('/:id', function(req, res) {
    return Equipa.remove(req.params.id)
      .then(data => res.jsonp(data))
      .catch(erro => res.jsonp(erro))
  });

module.exports = router;
