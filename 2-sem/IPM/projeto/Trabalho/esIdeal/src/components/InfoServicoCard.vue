<template>
    <div class="menu-container">
        <div class="card">
            <div class="title">
                <h1>Informação do Serviço</h1>
            </div>
            <div class="flex-container">
                <div class="element">
                    <h1>Designação:</h1>
                    <h2>{{ serviceData.descr }}</h2>
                </div>
                <div class="element">
                    <h1>Estado:</h1>
                    <h2>{{ currentState }}</h2>
                </div>
                <div class="element">
                    <h1>Duração:</h1>
                    <h2>{{ serviceData.duração }} minutos</h2>
                </div>
                <div class="element">
                    <h1>Chegada:</h1>
                    <h2>{{ formattedDate(chegada) }}</h2>
                </div>
                <div class="element">
                    <h1>Término:</h1>
                    <h2>{{ data ? formattedDate(data) : 'Não indicado' }}</h2>
                </div>
            </div>
            <form class="form">
                <h1>Descrição:</h1>
                <div class="box">
                    <p>{{serviceData.descrição}}</p>
                </div>
            </form>
        </div>
    </div>
</template>

<script>
export default {
  name: 'InfoServicoCard',
  props: {
    serviceData: {
      type: Object,
      required: true,
    },
  },
  computed: {
    formattedDate() {
      return (date) => {
        if (date) {
          return `${date.dia}/${date.mes}/${date.ano} ${date.hora}:${date.minutos}`;
        }
        return 'Não indicado';
      };
    },
    currentState() {
      switch (this.serviceData.estado) {
        case 'realizado':
          return 'Terminado'
        case 'nafila':
          return 'Por realizar'
        case 'programado':
          return 'Por realizar'
        case 'parado':
          return 'Suspenso'
        case 'aDecorrer':
          return 'A Decorrer'
        default:
          return 'Erro'
      }
    },
    chegada() {
      return this.serviceData.chegada;
    },
    data() {
      return this.serviceData.data;
    },
  }
};
</script>

<style scoped>

.menu-container{
    width: 100%;
    height: 100%;
    display: flex;
    justify-content: center;
    align-items: center;
  
}

.menu-container .card{
    width: 771px;
    height: 570px;
    border-radius: 20px;
    background-color: #B7D6FF;
    display: grid;
    grid-template-rows: 75px 106px 376px;
    grid-template-columns: 100%;
    gap: 3px;
    border-color: #1E56A0;
    border-style: solid;
    border-width: 1px;
    grid-template-areas:
        "title"
        "flex-container"
        "form";
    
    margin-bottom: 50px;
    
}

.form{

    width: 100%;
    height: 100%;
    display: flex;
    flex-direction: column;
    align-items: center;

}
.form .box{

    width: 95%;
    height: 83%;
    border-radius: 5px;
    background-color: #FFFF;
    border-style: solid;
    border-width: 1px;
    text-align: justify;
    text-indent: 10px;
    border-color: #1E56A0;

}

.form .box p{
   
   font-family: "Lato",sans-serif;
   font-size: 20px;
   font-weight: normal;
   
}

.form h1{
    text-align: left;
    align-self: flex-start;
    margin-left: 20px;
    font-size: 18px;
    font-family: "Lato", sans-serif;
    font-weight: bold;
    color:rgba(14, 60, 121, 0.75);
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
    width: 20%; 
    text-align: center;
    font-size: 20px;
    font-family: "Lato", sans-serif;
    font-weight: bold;
    color: #000;
    
}
.flex-container{
    margin-top: 35px;
    grid-area: flex-container;
    width: 100%;
    height: 100%;
    display: flex;
    justify-content: space-evenly;
    gap:20px;
    flex-direction: row;
}



.element h1{
    width: 100%; 
    text-align: left;
    font-size: 18px;
    font-family: "Lato", sans-serif;
    font-weight: bold;
    color:rgba(14, 60, 121, 0.75);
    margin-bottom: -10px;
}
.element h2 {
    width: 100%;
    height: 100%;
    text-align: left;
    font-size: 18px;
    font-family: "Lato", sans-serif;
    font-weight: bold;
    color: #000;
}

@media (max-width: 1024px) {
  .menu-container .card{
    width: 90%;
    height: 90%;
  }

  .form h1{
    font-size: 16px;
  }

  .title h1{
    font-size: 18px;
  }
  .flex-container {
    margin-top: 20px;
    gap: 15px;
  }
  .element h1{
    font-size: 16px;
  }
  .element h2{
    font-size: 16px;
    text-align: center;
  }

  .form .box {

    width: 95%;
    height: 73%;

  }

  .form .box p{
    font-size: 18px;
  }
}

@media (max-width: 800px) {
  .menu-container .card{
    width: 90%;
    height: 90%;
  }

  .form h1{
    font-size: 14px;
  }

  .title h1{
    font-size: 16px;
  }
  .flex-container {
    margin-top: 20px;
    gap: 15px;
  }
  .element h1{
    font-size: 12px;
  }
  .element h2{
    font-size: 12px;
    text-align: center;
  }

  .form .box {

    width: 95%;
    height: 73%;

  }

  .form .box p{
    font-size: 14px;
  }
}

</style>