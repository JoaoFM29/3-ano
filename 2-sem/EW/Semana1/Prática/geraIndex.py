import json

def chaveOrd(emd):
    return emd["dataEMD"]

f = open("emd.json")
bd = json.load(f)
f.close()

bd.sort(reverse=True, key = chaveOrd)


preHTML = f"""
<!DOCTYPE html>
<html>

    <head>
        <title>Lista de Exames Médicos Desportivos</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <meta charset="utf-8"/> 
        <link rel="stylesheet" href="w3.css">
    </head>

<body>

    <div class="w3-card-4">

        <header class="w3-container w3-blue-gray">
          <h3>Lista de Exames Médicos Desportivos</h3>
        </header>
        
        <div class="w3-container">
            <ul class="w3-ul w3-card-4" style="width:50%">"""

posHTML = f"""
            </ul>
        </div>
        
        <footer class="w3-container w3-blue-gray">
            <h5>Generated by EMDApp::EngWeb2024::A100740 </h5>
        </footer>        
    </div> 

</body>

</html>
"""

conteudo = ""

for e in bd:
    conteudo += f"""
        <li>
            <a href="emd{e['index']}.html">
            {e['dataEMD']}: {e['nome']['primeiro']}{e['nome']['último']}</a>
        </li>
    """
    
pagHTML = preHTML + conteudo + posHTML
f = open("EMDSite/Index.html", 'w')
f.write(pagHTML)
f.close()