var express = require('express');
var router = express.Router();
var axios = require('axios')

/* GET lista compositositores . */
router.get('/', function(req, res, next) { 
  var d = new Date().toISOString().substring(0, 16)
  axios.get("http://localhost:16000/contratos")
  .then(resp =>{
      contratos = resp.data
      res.status(200).render("contratosPage", {'lContratos' : contratos, 'date' : d})
  })
  .catch(erro =>{
      res.status(501).render('error', {'error' : erro})
  })
});

router.get('/:idContrato', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  var id = req.params.idContrato
  axios.get("http://localhost:16000/contratos/" +id)
  .then(resp =>{
      contrato = resp.data
      res.status(200).render("contratoPage", {'contrato' : contrato, 'date' : d})
  })
  .catch(erro =>{
      res.status(503).render('error', {'error' : erro})
  })
});

router.get('/entidades/:nipc', function(req, res, next) {
  var d = new Date().toISOString().substring(0, 16)
  var id = req.params.nipc

  axios.get("http://localhost:16000/contratos?entidade=" + id)
  .then(resp => {
      if (resp.data && resp.data.length > 0) {
          res.status(200).render("entidadePage", {'lContratos' : resp.data, 'date' : d})
      } else {
          res.status(404).render('error', {'error' : 'Nenhum contrato encontrado para a entidade especificada.'})
      }
  })
  .catch(erro => {
      // Lidar com erros de requisição para os contratos
      res.status(503).render('error', {'error' : erro})
  })
});


module.exports = router;
