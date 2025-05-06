<template>
  <div id="service-layout">
    <GoBackButton id="go-back-menu" />
    <InfoVeiculosCard id="info-veic-card" :vehicleData="vehicleData" />
    <InfoClientCard id="info-client-card" :clientData="clientData" />
    <InfoServicoCard id="info-servico-card" :serviceData="serviceData" />
    <SinalizaCard v-if="showSinalizaCard && isDataLoaded" id="sinaliza-card" :serviceData="serviceData" @mudarServicoEsq="handleBtnEsqClick" @mudarServicoDir="handleBtnDirClick" />
  </div>
  <Modal :open="isOpent" @close="isOpent = !isOpent">
    <TerminarComponent :serviceData="serviceData" :servicosPossiveis="servicosPossiveis" />
  </Modal>
  <Modal :titulo="'Não é possível acabar o serviço'" :open="isOpens" @close="isOpens = !isOpens">
    <SuspenderComponent :serviceData="serviceData" />
  </Modal>
</template>

<script>

import { useAuthStore } from '../store/authStore';
import axios from 'axios';
import { ref } from "vue";

import GoBackButton from '../components/GoBackButton.vue';
import InfoVeiculosCard from '../components/InfoVeiculosCard.vue';
import InfoClientCard from '../components/InfoClientCard.vue';
import InfoServicoCard from '../components/InfoServicoCard.vue';
import SinalizaCard from '../components/SinalizaCard.vue';
import SuspenderComponent from '../components/ModalComps/SuspenderComponent.vue';
import TerminarComponent from '../components/ModalComps/TerminarComponent.vue';
import Modal from "../components/Modal.vue";

const JSON_SERVER_URL = 'http://localhost:3000';

export default{
    name: "ServicePage",
    components: {
      GoBackButton,
      InfoVeiculosCard,
      InfoClientCard,
      InfoServicoCard,
      SinalizaCard,
      Modal,
      SuspenderComponent,
      TerminarComponent
  },
  data() {
    return {
      serviceData: {},
      vehicleData: {},
      clientData: {},
      servicosPossiveis: [],
      authStore: useAuthStore(),
      isDataLoaded: false // Nova flag para controlar se os dados foram carregados

    };
  },
  async mounted() {
    if (this.authStore.user) {
      await this.fetchData();
      this.isDataLoaded = true; // Marca os dados como carregados
    }
    else {
      this.$router.push({ name: 'login' });
    }
  },
  computed: {
    showSinalizaCard () {
      return (this.serviceData.estado !== 'realizado'  && this.isDataLoaded);
    }
  },
  setup() {
    const isOpent = ref(false);
    const isOpens = ref(false);
    
    return { isOpent , isOpens};
  },
  methods : {
    async fetchData() {
      try {
        const servicesResponse = await this.fetchServiceData(this.$route.params.serviceID);
        const servicesDefResponse = await this.fetchServiceDefinitionData(servicesResponse.data["service-definitionId"]);
        const servicesVecResponse = await this.fetchVehicleData(servicesResponse.data["vehicleId"]);
        const servicesCliResponse = await this.fetchClientData(servicesVecResponse.data["clientId"]);
        const servicesVecTypeResponse = await this.fetchVehicleTypeData(servicesVecResponse.data["vehicle-typeId"]);
        const AllServicesResponse = await this.fetchAllServiceData();
        
        this.serviceData = {...servicesDefResponse.data,...servicesResponse.data};
        this.vehicleData = servicesVecResponse.data;
        this.clientData = servicesCliResponse.data;
        this.servicosPossiveis = servicesVecTypeResponse.data;

        const poss = servicesVecTypeResponse.data.serviços;
        this.servicosPossiveis = []
        for (let i = 0; i < AllServicesResponse.data.length; i++) {
          
        if (poss.includes(AllServicesResponse.data[i].id)){
          this.servicosPossiveis.push(AllServicesResponse.data[i]);
        }
        }
      } catch (error) {
        console.error('Error fetching data:', error);
      }
    },

    async fetchServiceData(serviceID) {
      try {
        const response = await axios.get(`${JSON_SERVER_URL}/services/` + serviceID);
        return response; 

      } catch (error) {
        const userServices = this.authStore.user['serviços-realizados'];
        const foundService = userServices.find(service => service.id === serviceID);
        if (foundService) {
          return { "data": foundService };
        } else {
          console.error('Error fetching data on pinia:', error);
        }
      }
    },
    async fetchAllServiceData() {
      const response = await axios.get(`${JSON_SERVER_URL}/service-definitions`);
      return response;
    },
    async fetchServiceDefinitionData(serviceDefinitionId) {
      const response = await axios.get(`${JSON_SERVER_URL}/service-definitions/` + serviceDefinitionId);
      return response;
    },
    async fetchVehicleData(vehicleId) {
      const response = await axios.get(`${JSON_SERVER_URL}/vehicles/` + vehicleId);
      return response;
    },
    async fetchClientData(clientId) {
      const response = await axios.get(`${JSON_SERVER_URL}/clients/` + clientId);
      return response;
    },
    async fetchVehicleTypeData(type) {
      const response = await axios.get(`${JSON_SERVER_URL}/vehicle-types/` + type);
      return response;
    },
    handleBtnEsqClick(data) {
      this.serviceData = data
      switch (this.serviceData.estado) {
        case 'aDecorrer':
          // Handle ao Terminar Serviço
          this.isOpent = true
          break;
        case 'parado':
          // Handle ao Cancelar Serviço
          this.serviceData.estado = 'realizado';
          axios.patch(`${JSON_SERVER_URL}/services/`+this.serviceData.id,this.serviceData);
          break;
        default:
          // // Handle ao Começar Serviço 
          this.serviceData.estado = 'aDecorrer';
          // axios.patch(`${JSON_SERVER_URL}/services/`+this.serviceData.id,this.serviceData);
          
          break;
      }
    },
    handleBtnDirClick(data) {
      this.serviceData = data
      switch (this.serviceData.estado) {
        case 'aDecorrer':
          // Handle ao Suspender Serviço
          this.isOpens = true
        
          break;
        case 'parado':
          // Handle ao Continuar Serviço
          this.serviceData.estado ='aDecorrer'
          axios.patch(`${JSON_SERVER_URL}/services/`+this.serviceData.id,this.serviceData);
        
          break;
        default:
          break;
      }
    }
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
#service-layout {
    display: grid;
    height: 100%;
    grid-template-columns: 35% 65%;
    grid-template-rows: repeat(13, 7.69%);
    gap: 0px;
    grid-template-areas:
      ". ."
      "go-back-menu info-servico-card"
      "info-veic-card info-servico-card"
      "info-veic-card info-servico-card"
      "info-veic-card info-servico-card"
      "info-veic-card info-servico-card"
      "info-veic-card info-servico-card"
      "info-veic-card info-servico-card"
      "info-veic-card info-servico-card"
      "info-client-card sinaliza-card"
      "info-client-card sinaliza-card"
      "info-client-card sinaliza-card"
      "info-client-card sinaliza-card";
}

#go-back-menu{
    grid-area: go-back-menu;
}


#info-veic-card{
    grid-area: info-veic-card;
}

#info-client-card{
    grid-area: info-client-card;
}

#info-servico-card{
    grid-area: info-servico-card;
}

#sinaliza-card{
    grid-area: sinaliza-card;
}

</style>
