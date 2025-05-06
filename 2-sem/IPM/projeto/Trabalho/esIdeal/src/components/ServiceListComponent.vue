<template>
    <div class="service-list-container">
      <div class="service-list">
        <!-- Renderiza ServiceCard ou HistoryCard com base na rota -->
        <component v-for="(service, index) in displayList" :key="service.id" :is="cardComponent" :service="service"/>           
      </div>
    </div>
  </template>
  
  <script>
  import ServiceCard from './ServiceCard.vue';
  import HistoryCard from './HistoryCard.vue';
  import { computed } from 'vue';
  import { useRoute } from 'vue-router';
  
  export default {
    name: 'ServiceListComponent',
    props: {
      displayList: {
        type: Array,
        required: true
      }
    },
    components: {
      ServiceCard,
      HistoryCard
    },
    setup() {
      const route = useRoute();

      const cardComponent = computed(() => {
        const path = route.path;

        // Verifica se o caminho começa com '/home'
        if (path.startsWith('/home')) {
          return ServiceCard;
        }
        
        // Verifica se o caminho começa com '/history'
        if (path.startsWith('/history')) {
          return HistoryCard;
        }

        // Se não corresponder a nenhum caso acima, retorne um componente padrão
        return ServiceCard; // ou outro componente padrão desejado
      });

      return {
        cardComponent
      };
    }
  };
  </script>
  
  <style scoped>
  .service-list-container {
    height: 85%; 
    margin-left: 50px;
    margin-top: 50px;
    overflow-y: scroll;
    overflow-x: hidden;
    width: 982px;
    padding-right: 50px;
  }
  
  .service-list-container::-webkit-scrollbar {
    width: 30px;
  }
  
  .service-list-container::-webkit-scrollbar-track {
    margin-left: 200px;
    background-color: #F1F0F0;
    border-radius: 20px;
  }
  
  .service-list-container::-webkit-scrollbar-thumb {
    background-color: #B5B5B5;
    border-radius: 20px;
  }
  
  .service-list {
    width: 100%;
  }

  @media (max-width: 1350px) {
    .service-list-container {
      margin-left: 20px;
      margin-top: 20px;
      width: 900px;
      padding-right: 30px;
    }
  }

  @media (max-width: 1200px) {
    .service-list-container {
      margin-left: 10px;
      margin-top: 20px;
      width: 800px;
      padding-right: 10px;
    }
  }


  @media (max-width: 1024px) {
    .service-list-container {
      margin-left: 20px;
      margin-top: 20px;
      width: 780px;
      padding-right: 10px;
    }
    .service-list-container::-webkit-scrollbar {
      width: 25px;
    }

  }

  @media (max-width: 990px) {
    .service-list-container {
      margin-left: 20px;
      margin-top: 20px;
      width: 700px;
      padding-right: 10px;
    }
    .service-list-container::-webkit-scrollbar {
      width: 25px;
    }

  }

  @media (max-width: 800px) {
    .service-list-container {
      margin-left: 0px;
      margin-top: 20px;
      width: 720px;
      padding-right: 10px;
    }
    .service-list-container::-webkit-scrollbar {
      width: 15px;
    }

  }

  @media (max-width: 700px) {
    .service-list-container {
      margin-left: 0px;
      margin-top: 20px;
      width: 610px;
      padding-right: 10px;
    }
  }
  </style>
  
  