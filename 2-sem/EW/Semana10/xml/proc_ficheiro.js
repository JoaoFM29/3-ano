/* Processamento de um ficheiro XML em JS
   2024-03-30 by jcr
*/

var fs = require('fs'),
   xml2js = require('xml2js');

var parser = new xml2js.Parser();
fs.readFile(__dirname + '/agenda.xml', function(err, data) {
   if(err){
      console.log("Ocorreu um erro: " + err)
   }
   else{
      parser.parseString(data, function (err, result) {
         console.dir(result);
         console.dir(result.agenda.entrada)
         console.dir(result.agenda.entrada[1])
         console.dir(result.agenda.entrada[1].$.id)
     });
   }
});
