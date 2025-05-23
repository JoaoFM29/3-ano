import json

f = open("emd.json")
bd = json.load(f)
f.close()

for e in bd:
    f = open('./EMDSite/emd'+str(e['index'])+'.html', 'w')
    pagHTML = f"""
    <!DOCTYPE html> 
    <html>

        <head>
            <title>Exame Médico Desportivo : {e['nome']['primeiro']}{e['nome']['último']} </title>
            <meta name="viewport" content="width=device-width, initial-scale=1">
            <link rel="stylesheet" href="w3.css">
            <meta charset="utf-8"/> 
        </head>

    <body>

        <div class="w3-card-4">

            <header class="w3-container w3-blue-gray">
            <h3>Exame Médico Desportivo : {e['nome']['primeiro']}{e['nome']['último']}</h3>
            </header>
            
            <div class="w3-container">
                <table class="w3-table w3-striped">
                    <tr>
                        <td><b>Data do EMD</b></td> <td>{e['dataEMD']}</td>
                    </tr>
                    <tr>
                        <td><b>Idade</b></td> <td>{e['idade']}</td>
                    </tr>
                    <tr>
                        <td><b>Género</b></td> <td>{e['género']}</td>
                    </tr>
                    <tr>
                        <td><b>Modalidade</b></td> <td>{e['modalidade']}</td>
                    </tr>
                    <tr>
                        <td><b>Clube</b></td> <td>{e['clube']}</td>
                    </tr>
                    <tr>
                        <td><b>Resultado</b></td> <td><b>{e['resultado']}</b></td>
                    </tr>
                </table>
            </div>
            
            <footer class="w3-container w3-blue-gray">
                <h5>Generated by EMDApp::EngWeb2024::A100740 </h5>
                <adress>
                <a href ="index.html">Voltar à página principal</a>
                </adress>
            </footer>        
        </div> 

    </body>

    </html>
    """
    f.write(pagHTML)
    f.close()