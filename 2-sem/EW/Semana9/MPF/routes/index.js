var express = require('express');
var router = express.Router();
var jsonfile = require('jsonfile')
var fs = require('fs')
var multer = require('multer')

var upload = multer({dest: 'uploads'})

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

router.post('/files', upload.single('myFile'), (req, res) => {
  console.log('cdir: ' + __dirname)
  let oldPath = __dirname + '/../' + req.file.path
  console.log('old: ' + oldPath)
  let newPath = __dirname + '/../public/fileStore/' + req.file.originalname
  console.log('new: ' + newPath)

  fs.rename(oldPath,newPath, err => {
    if(err) throw err
  })

  var date = new Date().toISOString().substring(0,19)
  var files = jsonfile.readFileSync(__dirname + '/../data/dbFiles.json')

  files.push({
    date: date,
    name: req.file.originalname,
    mimetype: req.file.mimetype,
    size: req.file.size
  })

  jsonfile.writeFileSync(__dirname + '/../data/dbFiles.json', files)

  res.redirect('/')
})

module.exports = router;
