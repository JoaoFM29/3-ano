<template>
    <div class="container">
        <div class="card">
            <div class="title">
                <h1>Informações do Veículo</h1>
            </div>
            <div class="element" id="matricula">
                <h1>Matrícula:</h1>
                <h2>{{ vehicleData.id }}</h2>
            </div>
            <div class="element" id="marca">
                <h1>Marca:</h1>
                <h2>{{ vehicleData.marca }}</h2>
            </div>
            <div class="element" id="modelo">
                <h1>Modelo:</h1>
                <h2>{{ vehicleData.modelo }}</h2>
            </div>
            <div class="element" id="motor">
                <h1>Motor</h1>
                <h2 v-if="vehicleData['vehicle-typeId'] === 'gasolina'"> Motor a Combustão</h2>
                <h2 v-else-if="vehicleData['vehicle-typeId'] === 'gasoleo'">Motor a Combustão</h2>
                <h2 v-else-if="vehicleData['vehicle-typeId'] === 'eletrico'">Motor Elétrico</h2>
                <h2 v-else-if="vehicleData['vehicle-typeId'] === 'hibrido'">Híbrido</h2>
            </div>
            <div class="element" id="cilindrada" v-if="vehicleData['vehicle-typeId'] === 'gasolina' || vehicleData['vehicle-typeId'] === 'gasoleo'">
                <h1>Cilindrada</h1>
                <h2>{{ vehicleData.cilindrada }}</h2>
            </div>
            <div class="element" id="cilindrada" v-else-if="vehicleData['vehicle-typeId'] === 'eletrico'">
                <h1>Potência</h1>
                <h2>{{ vehicleData.potencia }}</h2>
            </div>
            <div class="element" id="cilindrada" v-else-if="vehicleData['vehicle-typeId'] === 'hibrido'">
                <h1>Cilindrada e Potência</h1>
                <h2>{{ vehicleData.cilindrada }} e {{ vehicleData.potencia }}</h2>
            </div>
            <div class="element" id="kilo">
                <h1>Kilometragem:</h1>
                <h2>{{ vehicleData.kms }}  km</h2>
            </div>
        </div>
    </div>
</template>

<script>

export default {
  name: 'InfoVeiculosCard',
  props: {
    vehicleData: {
      type: Object,
      required: true,
    },
  },
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
    height: 439px;
    border-radius: 20px;
    background-color: #B7D6FF;
    display: grid;
    grid-template-rows: repeat(7,13.3%);
    grid-template-columns: 100%;
    gap: 3px;
    border-color: #1E56A0;
    border-style: solid;
    border-width: 1px;
    grid-template-areas:
        "title"
        "matricula"
        "marca"
        "modelo"
        "motor"
        "cilindrada"
        "kilo";
    
}

#matricula {
    grid-area: matricula;
}
#marca {
    grid-area: marca;
}

#modelo {
    grid-area: modelo;
}

#motor {
    grid-area: motor;
}

#cilindrada {
    grid-area: cilindrada;
}

#kilo {
    grid-area: kilo;
}


.title {
    grid-area: title;
    width: 99.8%;
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
    background-color: #B7D6FF;
    border-color: #1E56A0;
    border-style: none;
    border-radius: 20px;
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
.element h2{
    width: 100%;
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
    height: 400px;
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