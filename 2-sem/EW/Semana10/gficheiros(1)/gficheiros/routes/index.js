var express = require('express');
var router = express.Router();
var jsonfile = require('jsonfile')
var fs = require('fs')

var multer = require('multer')
var upload = multer({dest: 'uploads'})

/* GET home page. */
router.get('/', function(req, res) {
  var date = new Date().toISOString().substring(0,19)
  jsonfile.readFile(__dirname + '/../data/dbFiles.json', (error, fileList) => {
    if(error){
      res.render('error', {error: error})
    }
    else{
      res.render('index', { files: fileList, d: date })
    }
  })
});

router.get('/fileContents/:fname', function(req, res) {
  var contents = fs.readFileSync(__dirname + '/../public/fileStore/' + req.params.fname)
  res.send(contents)
});

/* Download request */
router.get('/download/:fname', function(req, res) {
  res.download(__dirname + '/../public/fileStore/' + req.params.fname)
});

/* File submission */
router.post('/files', upload.single('myFile'), (req, res) => {
  console.log('cdir: ' + __dirname)
  let oldPath = __dirname + '/../' + req.file.path
  console.log('old: ' + oldPath)
  let newPath = __dirname + '/../public/fileStore/' + req.file.originalname 
  console.log('new: ' + newPath)

  fs.rename(oldPath, newPath, error => {
    if(error) throw error
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
