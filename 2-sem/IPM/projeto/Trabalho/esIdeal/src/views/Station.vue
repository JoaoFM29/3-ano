<template>
    <div id="home-layout">
      <div class="content">
        <h1>Bem-vindo, {{ mechanicName }}</h1>
        <h2>Escolha o seu posto</h2>
        <StationListComponent :stationData="stationData" />
        <EndSession id="session" />
      </div>
    </div>
  </template>
  
  <script>
  import axios from 'axios';
  import { useAuthStore } from '../store/authStore';

  import StationListComponent from '../components/StationListComponent.vue';
  import EndSession from '../components/EndSession.vue';
  
  const JSON_SERVER_URL = 'http://localhost:3000';
  
  export default {
    name: "Station",
    components: {
      StationListComponent,
      EndSession
    },
    data() {
      return {
        stationData: [],
        mechanicData: {},    
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
    computed: {
      mechanicName() {
        return this.mechanicData ? this.mechanicData.nome : '';
      }
    },
    methods: {
      async fetchData() {

        try {
          const stationResponse = await this.fetchStationData();
          this.stationData = stationResponse.data;

          this.mechanicData = this.authStore.user;
        } catch (error) {
          console.error('Error fetching data:', error);
        }
      },
      
      async fetchStationData() {
        const response = await axios.get(`${JSON_SERVER_URL}/service-stations`);
        return response;
      },
    }
  };
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
    grid-template-rows: 99% 1%;
    grid-template-columns: repeat(3, 1fr);
    gap: 1px;
    grid-template-areas:
      ".      cont     ."
      ".  session . ";
    overflow: auto;
  }

  #session{
    width: 25%;
    height: 3%;
    margin-top: 100px;
    padding-bottom: 10px;
    grid-area: session;
}

  
  .content {
    width: 100%;
    grid-area: cont;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
  }
  
  h1 {
    font-size: 40px;
    font-family: 'Lato',sans-serif;
    font-weight: bold;
    color: #1E56A0;
    margin-bottom: 5px;
  }

  h2 {
    font-size: 25px;
    font-family: 'Lato',sans-serif;
    color: #6BABFF;
    margin-top: 0;
  }

@media (max-width: 1024px){
  #session{
    margin-top: 20px;
  }
}

  </style>
  