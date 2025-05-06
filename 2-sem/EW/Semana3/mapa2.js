var http = require('http')
var url = require('url')

http.createServer(function(req,res) {
    res.writeHead(200, {'Content-Type': 'text/html; charset=utf-8'});
    var q = url.parse(req.url, true).query
    var a = parseInt(q.a, 10);
    var b = parseInt(q.b, 10);

    if (isNaN(a) || isNaN(b)) {
        var txt = 'Invalid parameters: Please provide valid numbers for "a" and "b".'
        res.end(txt);
    } else {
        var result = a + b;
        var txt = a + " + " + b + " = " + result;
        console.log(txt);
        res.end(txt);
    }
}).listen(7777);
