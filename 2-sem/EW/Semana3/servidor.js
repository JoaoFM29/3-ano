var http = require('http')

http.createServer(function(req,res) {
    res.writeHead(200, {'Content-Type': 'text/HTML'});
    res.write('<p> <b> Ola turma de 2024!</b> </p> ');
    res.end();
}).listen(7777);
