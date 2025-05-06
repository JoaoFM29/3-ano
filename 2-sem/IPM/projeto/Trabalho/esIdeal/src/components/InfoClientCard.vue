<template>
    <div class="container">
        <div class="card">
            <div class="title">
                <h1>Informações do Cliente</h1>
            </div>
            <div class="element" id="nome">
                <h1>Nome:</h1>
                <h2>{{clientData.nome}}</h2>
            </div>
            <div class="element" id="email">
                <h1>Email:</h1>
                <h2>{{clientData.email}}</h2>
            </div>
            <div class="element" id="morada">
                <h1>Morada:</h1>
                <h2>{{clientData.morada}}</h2>
            </div>
            <div class="element" id="contacto">
                <h1>Contacto:</h1>
                <h2>{{clientData.telefone}}</h2>
            </div>
        </div>
    </div>
</template>

<script>

export default {
  name: 'InfoClientCard',
  props: {
  clientData: {
      type: Object,
      required: true,
    }
  }
}

</script>

<style scoped>

.container{
    width: 100%;
    height: 100%;
    display: flex;
    flex-direction: row;
    justify-content: center;
    align-items: center;
}

.container .card{
    width: 312px;
    height: 332px;
    border-radius: 20px;
    background-color: #B7D6FF;
    display: grid;
    grid-template-rows: repeat(6,19%);
    grid-template-columns: 100%;
    gap: 3px;
    border-color: #1E56A0;
    border-style: solid;
    border-width: 1px;
    grid-template-areas:
        "title"
        "nome"
        "email"
        "morada"
        "contacto";
    
    margin-bottom: 50px;
    
}
#nome{
    grid-area: nome;
}
#email{
    grid-area: email;
}
#morada{
    grid-area: morada;
}
#contacto{
    grid-area: contacto;
}

.title {
    grid-area: title;
    width: 99.5%;
    height: 100%;
    border-radius: 20px;
    background-color: #8BBDFF;
    border-color: #1E56A0;
    border-style: solid;
    border-width: 1px;
    display: flex;
    flex-direction: row;
    justify-content: center;
    align-items: center;
    margin-top: -1px;
    
}
.title h1{
    width: 64%; 
    text-align: center;
    font-size: 20px;
    font-family: "Lato", sans-serif;
    font-weight: bold;
    color: #000;
    
}

.element {
    width: 100%;
    height: 100%;
    border-color: #1E56A0;
    border-style: none;
    border-radius: 20px;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
}
.element h1{
    width: 100%; 
    text-align: center;
    font-size: 18px;
    font-family: "Lato", sans-serif;
    font-weight: bold;
    color:rgba(14, 60, 121, 0.75);
    margin-bottom: -10px;
}
.element h2 {
    width: 80%;
    height: 24px;
    text-align: center;
    font-size: 18px;
    font-family: "Lato", sans-serif;
    font-weight: bold;
    color: #000;
}

@media (max-width: 1024px) {
  .container .card{
    width: 284px;
    height: 302px;
  }

  .title h1{
    font-size: 18px;
  }
  .element h1{
    font-size: 16px;
  }

  .element h2 {
    font-size: 16px;
  }
}
</style>