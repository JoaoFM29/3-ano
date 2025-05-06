/* Processamento de um ficheiro XML em JS
   2024-03-30 by jcr
*/

var fs = require('fs'),
   xml2js = require('xml2js');

var parser = new xml2js.Parser();
fs.readFile(__dirname + '/aval-alunos.xml', function(err, data) {
   if(err){
      console.log("Ocorreu um erro: " + err)
   }
   else{
      parser.parseString(data, function (err, result) {
         console.log(JSON.stringify(result))

     });
   }
});
