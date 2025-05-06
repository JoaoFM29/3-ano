var http = require('http');
var fs = require('fs');

http.createServer(function(req,res){
    var d = new Date().toISOString().substring(0.16)
    console.log(req.method + " " + req.url + " " + d)
    fs.readFile('pag1.html', function(erro,dados){
        if(!erro){
            res.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'})
            res.write(dados)
            res.end()
        }
        else{
            res.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'})
            res.write("<pre>" + erro + "</pre>")
            res.end()
        }
    })
}).listen(7777)