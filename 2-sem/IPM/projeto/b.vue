<template>
  <div class="menus-container">
    <div class="ord-wrapper" id="data">
      <h1>Data:</h1>
      <div class="dropdown-item">
        <div class="date-section">
          <label for="startDate">De:</label>
          <input type="date" id="startDate" name="startDate" v-model="startDate">
        </div>
        <div class="date-section">
          <label for="endDate">Até:</label>
          <input type="date" id="endDate" name="endDate" v-model="endDate">
        </div>
      </div>
    </div>
    <div class="ord-wrapper" id="matricula">
      <h1>Matrícula:</h1>
      <div class="dropdown-item">
        <input type="text" id="matriculaInput" name="matricula" v-model="matricula" class="input-field">
      </div>
    </div>
    <div class="ord-wrapper" id="designacao">
      <h1>Designação:</h1>
      <div class="dropdown-item">
        <input type="text" id="designacaoInput" name="designacao" v-model="designacao" class="input-field">
      </div>
    </div>
    <div class="ord-wrapper" id="buttonContainer">
      <button id="clearFiltersButton" @click="clearFilters">Limpar Filtros</button>
      <button id="searchButton" @click="applyFilters">Pesquisar</button>
    </div>
  </div>
</template>

<script>
import axios from 'axios';

const JSON_SERVER_URL = 'http://localhost:3000';

export default {
  name: 'DropMenusBar2',
  data() {
    return {
      startDate: '',
      endDate: '',
      matricula: '',
      designacao: '',
      originalServiceList: [], // Armazenar os serviços originais localmente
      filteredServiceList: [], // Lista de serviços filtrada
    };
  },
  mounted() {
    this.fetchData();
  },
  methods: {
    async fetchData() {
      try {
        const servicesResponse = await axios.get(`${JSON_SERVER_URL}/services`);
        this.originalServiceList = servicesResponse.data; // Armazenar os serviços originais
      } catch (error) {
        console.error('Error fetching data:', error);
      }
    },
    filtraRealizados(serviceList, estado) {
      return serviceList.filter(service => service.estado === estado);
    },
    filterByCustomDate(serviceList, startDate, endDate) {
      const start = new Date(startDate);
      const end = new Date(endDate);
      return serviceList.filter(service => {
        const serviceDate = new Date(
            service.chegada.ano,
            service.chegada.mes - 1,
            service.chegada.dia,
            service.chegada.hora,
            service.chegada.minutos
        );
        return serviceDate >= start && serviceDate <= end;
      });
    },
    filterByMatricula(serviceList, matricula) {
      const matriculaRegex = /^\d{2}-\d{2}-[A-Z]{2}$/;
      return serviceList.filter(service =>
          service.vehicleId === matricula
      );
    },
    filterByDesignacao(serviceList, designacao) {
      return serviceList.filter(service =>
          service.descrição === designacao
      );
    },
    applyFilters() {
      let copia = [...this.originalServiceList]; // copia dos serviços originais

      // Filtrar por serviço realizado
      copia = this.filtraRealizados(copia, "realizado");

      if (this.startDate && this.endDate) {
        copia = this.filterByCustomDate(copia, this.startDate, this.endDate);
      }

      // Filtrar por matrícula
      if (this.matricula) {
        copia = this.filterByMatricula(copia, this.matricula);
      }
      if (this.designacao) {
        copia = this.filterByDesignacao(copia, this.designacao);
      }

      // Emitir evento com os serviços filtrados
      this.$emit('filters-applied', copia);
    },
    clearFilters() {
      let copia = [...this.originalServiceList]; // copia dos serviços originais

      // Limpar os campos de filtro
      this.startDate = '';
      this.endDate = '';
      this.matricula = '';
      this.designacao = '';

      // Filtrar por serviço realizado
      copia = this.filtraRealizados(copia, "realizado");

      // Restaurar a lista original sem filtros
      this.$emit('filters-applied', copia);
    },
  },
};
</script>

<style scoped>
.menus-container {
  background-color: #FFF;
  border-bottom: 1px solid #1E56A0;
  border-left: 0px;
  display: grid;
  grid-template-rows: 85% 15%;
  grid-template-columns: 33.3% 33.3% 33.3%;
  gap: 0px;
  grid-template-areas:
          "data matricula designacao"
          ". . buttonContainer";
}

.ord-wrapper {
  display: flex;
  justify-content: center;
  align-items: center;
  flex-direction: row;
}

.ord-wrapper h1 {
  font-size: 16px;
  font-family: 'Inter', sans-serif;
  color: #616161;
  font-weight: normal;
  align-self: flex-start;
  margin-left: 38px;
}

.dropdown-item {
  cursor: pointer;
  transition: background-color 0.3s ease;
  display: flex;
  align-items: center;
  justify-content: center;
  width: 318px;
  height: 44px;
  background-color: #fff;
  border: 1px solid #000;
}

.dropdown-item:hover {
  background-color: #f5f5f5;
}

.date-section {
  display: flex;
  align-items: center;
  padding: 3px; /* espaçamento entre datas*/
}

.input-field {
  width: 90%;
  font-size: 16px;
  font-family: 'Inter', sans-serif;
  border: none;
  outline: none;
  padding: 0 10px;
}

#data, #matricula, #designacao {
  display: flex;
  flex-direction: column;
}

#buttonContainer {
  margin-right: 20px;
  display: flex;
  grid-area: buttonContainer;
  padding-bottom: 20px;
}

#searchButton, #clearFiltersButton {
  width: 200px;
  height: 50px;
  background-color: #B7D6FF;
  color: #0E3C79;
  border: 1px solid #1E56A0;
  border-radius: 20px;
  font-size: 18px;
  cursor: pointer;
  margin-left: 10px;
}

#searchButton:hover, #clearFiltersButton:hover {
  background-color: #A3C8FF;
}

</style>
