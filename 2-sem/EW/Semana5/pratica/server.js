// alunos_server.js
// EW2024 : 04/03/2024
// by jcr

var http = require('http')
var axios = require('axios')
const { parse } = require('querystring');

var templates = require('./templates')          // Necessario criar e colocar na mesma pasta
var static = require('./static.js')             // Colocar na mesma pasta

// Aux functions
function collectRequestBodyData(request, callback) {
    if(request.headers['content-type'] === 'application/x-www-form-urlencoded') {
        let body = '';
        request.on('data', chunk => {
            body += chunk.toString();
        });
        request.on('end', () => {
            callback(parse(body));
        });
    }
    else {
        callback(null);
    }
}

// Server creation

var alunosServer = http.createServer((req, res) => {
    // Logger: what was requested and when it was requested
    var d = new Date().toISOString().substring(0, 16)
    console.log(req.method + " " + req.url + " " + d)

    // Handling request
    if(static.staticResource(req)){
        static.serveStaticResource(req, res)
    }
    else{
        switch(req.method){
            case "GET": 
                 // GET /alunos --------------------------------------------------------------------
                if(req.url == '/alunos'){
                    axios.get('http://localhost:3000/alunos')
                    .then (resposta => {
                        res.writeHead(200, {'Content-Type': 'text/html'})
                        res.end(templates.studentsListPage(resposta.data, d))
                    })
                    .catch(erro => {
                        res.writeHead(520, {'Content-Type': 'text/html'}) //codigo 520 para quando falhar saber que foi aqui
                        res.end(templates.errorPage(erro, d))
                    })
                }
                
                // GET /alunos/:id --------------------------------------------------------------------
                else if(/\/alunos\/A[0-9]+/.test(req.url)){
                    axios.get('http://localhost:3000' + req.url)
                    .then (resposta => {
                        res.writeHead(200, {'Content-Type': 'text/html'})
                        res.end(templates.studentPage(resposta.data, d))
                    })
                    .catch(erro => {
                        res.writeHead(520, {'Content-Type': 'text/html'}) //codigo 520 para quando falhar saber que foi aqui
                        res.end(templates.errorPage(erro, d))
                    })
                }
                
                // GET /alunos/registo --------------------------------------------------------------------
                else if(req.url == '/alunos/registo'){
                    res.writeHead(200, {'Content-Type': 'text/html'})
                    res.end(templates.studentFormPage(d))
                }
               
                // GET /alunos/edit/:id --------------------------------------------------------------------
                else if(/\/alunos\/edit\/A[0-9]+/.test(req.url)){
                    var partes = req.url.split('/')
                    idAluno = partes[partes.length - 1];
                    axios.get('http://localhost:3000/alunos/' + idAluno)
                    .then (resposta => {
                        res.writeHead(200, {'Content-Type': 'text/html'})
                        res.end(templates.studentFormEditPage(resposta.data, d))
                    })
                    .catch(erro => {
                        res.writeHead(520, {'Content-Type': 'text/html'}) //codigo 520 para quando falhar saber que foi aqui
                        res.end(templates.errorPage(erro, d))
                    })
                }

                // GET /alunos/delete/:id --------------------------------------------------------------------
                else if(/\/alunos\/delete\/A[0-9]+/.test(req.url)){
                    var partes = req.url.split('/')
                    idAluno = partes[partes.length - 1];
                    axios.delete('http://localhost:3000/alunos/' + idAluno)
                    .then (resposta => {
                        res.writeHead(200, {'Content-Type': 'text/html'})
                        res.end(templates.studentPage(resposta.data, d))
                    })
                    .catch(erro => {
                        res.writeHead(521, {'Content-Type': 'text/html'}) //codigo 521 para quando falhar saber que foi aqui
                        res.end(templates.errorPage(erro, d))
                    })
                }
                // GET ? -> Lançar erro --------------------------------------------------------------------
                else{
                    res.writeHead(404, {'Content-Type': 'text/html'})
                    res.end(templates.errorPage(`Pedido não suportado: ${req.url}`, d))
                }
                break;
            case "POST":
                // POST /alunos/registo --------------------------------------------------------------------
                if(req.url == '/alunos/registo'){
                    collectRequestBodyData(req, result =>{
                        if(result){
                            axios.post('http://localhost:3000/alunos', result)
                            .then (resposta => {
                                res.writeHead(201, {'Content-Type': 'text/html'})
                                res.end(templates.studentPage(resposta.data, d))
                            })
                            .catch(erro => {
                                res.writeHead(520, {'Content-Type': 'text/html'}) //codigo 520 para quando falhar saber que foi aqui
                                res.end(templates.errorPage(erro, d))
                            })
                        }
                        else{
                            res.writeHead(201, {'Content-Type': 'text/html; charset=utf-8'})
                            res.write("<p> Unable to collect data from body.. </p>")
                            res.end()
                        }
                    })
                }
                
                // POST /alunos/edit/:id --------------------------------------------------------------------
                else if(/\/alunos\/edit\/A[0-9]+/.test(req.url)){
                    var partes = req.url.split('/')
                    idAluno = partes[partes.length - 1];
                    collectRequestBodyData(req, result =>{
                        if(result){
                            axios.put('http://localhost:3000/alunos/' + idAluno, result)
                            .then (resposta => {
                                res.writeHead(201, {'Content-Type': 'text/html'})
                                res.end(templates.studentPage(resposta.data, d))
                            })
                            .catch(erro => {
                                res.writeHead(520, {'Content-Type': 'text/html'}) //codigo 520 para quando falhar saber que foi aqui
                                res.end(templates.errorPage(erro, d))
                            })
                        }
                        else{
                            res.writeHead(201, {'Content-Type': 'text/html; charset=utf-8'})
                            res.write("<p> Unable to collect data from body.. </p>")
                            res.end()
                        }
                    })
                }
                // POST ? -> Lançar erro --------------------------------------------------------------------
                else{
                    res.writeHead(404, {'Content-Type': 'text/html'}) //codigo 520 para quando falhar saber que foi aqui
                    res.end(templates.errorPage(`Pedido POST não suportado: ${req.url}`, d))
                } 
                break;
            default: 
                // Outros metodos nao sao suportados
        }
    }
})

alunosServer.listen(7777, ()=>{
    console.log("Servidor à escuta na porta 7777...")
})



