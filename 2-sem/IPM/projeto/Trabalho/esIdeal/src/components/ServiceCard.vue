<template>
    <div class="service-card">
      <div class="info-row">
        <div class="info-item">
          <h1>Designação:</h1>
          <h2>{{ service.definition.descr }}</h2>
        </div>
        <div class="info-item">
          <h1>Estado:</h1>
          <h2>{{ currentState }}</h2>
        </div>
        <div class="info-item">
          <h1>Duração:</h1>
          <h2>{{ service.definition.duração }} minutos</h2>
        </div>
        <div class="info-item">
          <h1>Chegada:</h1>
          <h2>{{ dataFormatada(service.chegada) }}</h2>
        </div>
        <div class="info-item">
          <h1>Término:</h1>
          <h2>{{ dataFormatada(service.data) }}</h2>
        </div>
      <button class="details-button" @click="navigateToService"
                                      @mouseover="isHovered = true"
                                      @mouseout="isHovered = false"
                                      :class="{ 'button-hovered': isHovered }">
      Detalhes</button>
    </div>
   </div>
  </template>
  
  <script>

  import { useFromStore } from '../store/fromStore';

  export default {
    name: 'ServiceCard',
    data() {
      return {
        isHovered: false,
        fromStore: useFromStore()
      };
    },
    props: {
      service: {
        type: Object,
        required: true
      }
    },
    computed: {
    currentState() {
      switch (this.service.estado) {
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
  },
    methods: {
      dataFormatada(data) { 
      if (data instanceof Object) {
        const dia = data.dia;
        const mes = data.mes + 1;
        const ano = data.ano;
        let min = data.minutos;
        min = min < 10 ? `0${min}` : `${min}`;

        const hora = data.hora
        return `${dia}/${mes}/${ano} ${hora}:${min}`;
      } else {
        return 'Não indicado';
      }
    },
      navigateToService() {
        // Implemente a navegação para a rota com nome 'service'
        this.fromStore.from = true;
        this.$router.push({
              name: 'service',
              params: {
                serviceID: this.service.id
              }      
        });
      }
    }
  };
  </script>
  
  <style scoped>
  .service-card {
    display: flex;
    flex-direction: row;
    padding: 20px;
    background-color: #ffffff;
    border-width: 1px;
    border-style: solid;
    width: 95.7%; /* Ocupa 100% da largura disponível */
  }
  
  .info-row {
    display: flex;
    gap: 20px;
    width: 100%; /* Ocupa 100% da largura disponível */
  }
  
  .info-item {
    flex: 1; /* Distribui espaço igualmente entre os itens */
  }
  
  .info-item h1 {
    font-size: 18px;
    font-family: 'inter',sans-serif;
    font-weight: normal;
    color: #6F6A6A;
    margin-bottom: 5px;
  }
  
  .info-item h2 {
    font-size: 18px;
    font-family: 'inter',sans-serif;
    font-weight: normal;
    color: #000000;
    margin-top: 0;
  }
  
  .details-button {
    width: 120px;
    height: 40px;
    background-color: #1e56a0;
    color: #ffffff;
    font-size: 16px;
    font-weight: bold;
    border-radius: 5px;
    cursor: pointer;
    margin-top: 10px; /* Adicionar margem acima do botão */
  }
  .button-hovered {
  box-shadow: 0 3px 6px rgba(0, 0, 0, 0.3); 
}

  @media (max-width: 1350px) {
    .service-card {
       padding: 15px
    }
    .info-item h1 {
      font-size: 16px;
    }
    .info-item h2 {
      font-size: 16px;
    }
    .details-button {
      width: 90px;
      font-size: 14px;
    }
  }

  @media (max-width: 800px) {
    .service-card {
      padding: 12px
    }
    .info-item h1 {
      font-size: 13px;
    }
    .info-item h2 {
      font-size: 13px;
    }
    .details-button {
      width: 70px;
      font-size: 10px;
    }
  }

  </style>