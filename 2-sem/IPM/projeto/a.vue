<template>
  <div id="home-layout">
    <SideCardHistComponent id="info-card" />
    <FormMenuBar id="menu-bar" />
    <DropMenuBar2 id="menu-bar" @filters-applied="updateFilteredServiceList" />
    <div class="content">
      <HistoryList :serviceList="displayedServiceList" :startDate="startDate" :endDate="endDate" />
    </div>
  </div>
  <ChatBotComponent />
</template>

<script>


import axios from 'axios';

import SideCardHistComponent from "../components/SideCardHist.vue"
import FormMenuBar from "../components/formMenuBar.vue"
import DropMenuBar2 from '../components/dropMenusBar2.vue';
import ChatBotComponent from "../components/ChatBot.vue";
import HistoryList from '../components/HistoryList.vue';

const JSON_SERVER_URL = 'http://localhost:3000';

export default {
  name: "History",
  components: {
    SideCardHistComponent,
    FormMenuBar,
    DropMenuBar2,
    ChatBotComponent,
    HistoryList
  },
  data() {
    return {
      originalServiceList: [], // Lista original de serviços
      displayedServiceList: [], // Lista de serviços a ser exibida com ou sem filtros
      startDate: '2024-01-01', // Defina a data de início desejada
      endDate: '2024-12-31' // Defina a data de fim desejada
    };
  },
  async mounted() {
    await this.fetchData();
    this.displayedServiceList = [...this.originalServiceList]; // Inicialmente exibe todos os serviços
  },
  methods: {
    filtraRealizados(serviceList, estado) {
      return serviceList.filter(service => service.estado === estado);
    },
    async fetchData() {
      try {
        const response = await axios.get(`${JSON_SERVER_URL}/services`);
        this.originalServiceList = response.data;
        // Filtrar por serviço realizado
        this.originalServiceList = this.filtraRealizados(this.originalServiceList, "realizado");
      } catch (error) {
        console.error('Error fetching data:', error);
      }
    },
    updateFilteredServiceList(filteredServices) {
      this.displayedServiceList = filteredServices;
    },
  },
};
</script>


<style scope>
html, body {
  font-family: Inter;
  margin: 0;
  padding: 0;
  height: 100%;
}

#home-layout {
  display: grid;
  height: 100%;
  grid-template-rows: 353px 671px;
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

</style>