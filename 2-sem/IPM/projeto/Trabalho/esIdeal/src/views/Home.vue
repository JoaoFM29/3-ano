<template>
  <div id="home-layout">
    <InfoCardComponent :stationData="stationData" id="info-card" />
    <DropMenuBar id="menu-bar" @orderChanged="updateOrder" />
    <div class="content">
      <ServiceListComponent :displayList="displayList" />
    </div>
  </div>
  <ChatBotComponent />
</template>

<script>
import { useStationStore } from '../store/stationStore';
import { useAuthStore } from '../store/authStore';
import axios from 'axios';

import InfoCardComponent from '../components/InfoCard.vue';
import ChatBotComponent from '../components/ChatBot.vue';
import DropMenuBar from '../components/dropMenusBar.vue';
import ServiceListComponent from '../components/ServiceListComponent.vue'; 


const JSON_SERVER_URL = 'http://localhost:3000';

export default {
  name: "Home",
  components: {
    InfoCardComponent,
    ChatBotComponent,
    DropMenuBar,
    ServiceListComponent
  },
  data() {
    return {
      serviceList: [],
      displayList: [],
      auxList: [],
      defaultOrder: ['Data de Chegada', 'Por Realizar', 'Todos'],
      stationData: {},
      authStore: useAuthStore()
    };
  },
  async mounted() {
    if (this.authStore.user) {
        await this.fetchData();
      }
      else {
        this.$router.push({ name: 'login' });
      }
  },
  methods: {
    sortByArrivalDate() {
      this.displayList.sort((a, b) => {
        if (!a.chegada || !b.chegada) return 0;
        const dateA = new Date(a.chegada.ano, a.chegada.mes - 1, a.chegada.dia, a.chegada.hora, a.chegada.minutos);
        const dateB = new Date(b.chegada.ano, b.chegada.mes - 1, b.chegada.dia, b.chegada.hora, b.chegada.minutos);
        return dateA - dateB;
      });
    },
    sortByShortestDuration() {
      this.displayList.sort((a, b) => a.definition.duração - b.definition.duração);
    },
    sortByLongestDuration() {
      this.displayList.sort((a, b) => b.definition.duração - a.definition.duração);
    },
    sortByCompletionDate() {
      this.displayList.sort((a, b) => {
        if (!a.data && !b.data) return 0;
        if (!a.data) return 1;
        if (!b.data) return -1; 
        const dateA = new Date(a.data.ano, a.data.mes - 1, a.data.dia, a.data.hora, a.data.minutos);
        const dateB = new Date(b.data.ano, b.data.mes - 1, b.data.dia, b.data.hora, b.data.minutos);
        return dateB - dateA;
      });
    },
    takeEstado(){
      var arrayTemp;
      switch (this.defaultOrder[1]) {
        case 'Por Realizar':
          arrayTemp = this.displayList.filter(function (serv) {
          return serv.estado === 'nafila' ||serv.estado === 'programado';
          });
          break;
        case 'A Decorrer':
          arrayTemp = this.displayList.filter(function (serv) {
          return serv.estado === 'aDecorrer';
          });
          break;
        case 'Suspenso':
          arrayTemp = this.displayList.filter(function (serv) {
          return serv.estado === 'parado';
          });
          break;
        case 'Realizado':
          arrayTemp = this.displayList.filter(function (serv) {
          return serv.estado === 'realizado';
          });
          break;
        default: // TODOS
          arrayTemp = this.displayList;
          break;
      }
      this.displayList = arrayTemp;
      
    },
    takeAgendamento(){
      var arrayTemp;
      switch (this.defaultOrder[2]) {
        case 'Fila de Espera':
          arrayTemp = this.displayList.filter(function (serv) {
          return serv.agendamento === 'filaDeEspera';
          });
          break;
        case 'Programados':
          arrayTemp = this.displayList.filter(function (serv) {
          return serv.agendamento === 'programado';
          });
          break;
        default: // TODOS
          arrayTemp = this.displayList;
          break;
      }
      this.displayList = arrayTemp;
    },
    orderList() {
      this.displayList = this.auxList;
      switch (this.defaultOrder[0]) {
        case 'Data de Chegada':
          this.sortByArrivalDate();
          break;
        case 'Menor duração Média':
          this.sortByShortestDuration();
          break;
        case 'Maior duração Média':
          this.sortByLongestDuration();
          break;
        case 'Data de Conclusão':
          this.sortByCompletionDate();
          break;
        default:
          break;
      }
    },
    updateOrder(newOrder) {
      this.defaultOrder = newOrder;
      this.orderList();
      this.takeEstado();
      this.takeAgendamento();
    },
    async fetchData() {
      try {
        const [servicesResponse, definitionsResponse] = await Promise.all([
          axios.get(`${JSON_SERVER_URL}/services`),
          axios.get(`${JSON_SERVER_URL}/service-definitions`)
        ]);
        const stationResponse = await this.fetchStationData(this.$route.params.stationID);
        this.stationData = stationResponse.data

        //Guardar o posto globalmente
        const stationStore = useStationStore();
        stationStore.login(this.stationData);

        this.serviceList = servicesResponse.data.map(service => ({
          ...service,
          definition: definitionsResponse.data.find(def => def.id === service['service-definitionId'])
        }));

        //Filtra pela especialidade do mecanico
        const mechanicSpecialty = this.authStore.user.especialização;
        const stationid = stationStore.station.id;

        // Filtra apenas os serviços para o determinado posto
        this.auxList = [...this.serviceList].filter(service => service.postID === stationid);
        this.serviceList = this.auxList;
        
        if(mechanicSpecialty === "combustao") {
          const tipo1 = "gasoleo";
          const tipo2 = "gasolina";
          const response1 = await axios.get(`${JSON_SERVER_URL}/vehicle-types/${tipo1}`);
          const response2 = await axios.get(`${JSON_SERVER_URL}/vehicle-types/${tipo2}`);
          const servicesArray1 = response1.data.serviços;
          const servicesArray2 = response2.data.serviços;
          const vehicleTypes = servicesArray1.concat(servicesArray2);

          this.auxList =  [...this.serviceList].filter(service => {
            return vehicleTypes.includes(service['service-definitionId']);
          });
        }
        else if(mechanicSpecialty === "eletrico") {
          const tipo = "eletrico";
          const response = await axios.get(`${JSON_SERVER_URL}/vehicle-types/${tipo}`);
          const vehicleTypes = response.data.serviços;

          this.auxList =  [...this.serviceList].filter(service => {
            return vehicleTypes.includes(service['service-definitionId']);
          });
        }
      } catch (error) {
        console.error('Error fetching data:', error);
      }
      this.orderList();
      this.takeEstado();
      this.takeAgendamento();
    },
    async fetchStationData(stationID) {
      const response = await axios.get(`${JSON_SERVER_URL}/service-stations/` + stationID);
      return response;
    },
   

  }
}
</script>


<style scoped>
html, body {
  font-family: Inter;
  margin: 0;
  padding: 0;
  height: 100%;
}

#home-layout {
  display: grid;
  height: 100%;
  grid-template-rows: 217px 806px;
  grid-template-columns: 267px 36.8% 44.66%;
  gap: 1px;
  grid-template-areas:
    "info-card menu-bar menu-bar"
    "info-card cont cont";
    overflow: auto;

}

#chat-bot{
  grid-area: chat-bot;
}
#info-card{
  width: 100%;
  height: 100%;
  grid-area: info-card;
}

#menu-bar{
    width: 100%;
    height: 100%;
    grid-area: menu-bar;
  }
.content {
  padding: 20px;
  width: 95%;
  grid-area: cont;
}


@media (max-width: 1350px) {
  #home-layout {
    grid-template-columns: 210px 33.8% 44.66%;
  }
  .content{
    padding: 15px;
  }
}

@media (max-width: 1024px) {
  #home-layout {
    grid-template-columns: 160px 33.8% 44.66%;
  }
  .content{
    padding: 5px;
  }

}

@media (max-width: 800px) {
  #home-layout {
    display: grid;
    height: 100%;
    grid-template-columns: 100%;
    grid-template-rows: 150px 26.8% auto;
    gap: 1px;
    grid-template-areas:
    "info-card"
    "menu-bar"
    "cont";
    overflow: auto;
  }
}
</style>