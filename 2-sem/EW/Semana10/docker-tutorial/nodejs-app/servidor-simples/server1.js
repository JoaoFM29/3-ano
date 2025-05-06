var http = require('http')

http.createServer(function (req, res) {
    res.writeHead(200, {'Content-Type': 'text/plain; charset=utf-8'});
    res.end('Olá turma de 2024! Esta é a versão 3 do servidor...');
}).listen(7777);
console.log('Servidor à escuta na porta 7777...')
