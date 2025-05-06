<template>
  <div class="menus-container">
    <div class="Title">Filtros de pesquisa</div>

    <!-- Filtros de Data -->
    <div class="ord-wrapper" id="data">
      <h1>Data:</h1>
      <div class="dropdown-item">
        <div class="date-section">
          <label for="startDate">De:</label>
          <input type="date" id="startDate" name="startDate" v-model="startDate">
          <label for="endDate">Até:</label>
          <input type="date" id="endDate" name="endDate" v-model="endDate">
        </div>
      </div>
    </div>

    <!-- Filtros de Matrícula, Designação, Nome, Email e Contacto -->
    <div class="ord-wrapper" id="matricula">
      <h1>Matrícula:</h1>
      <div class="dropdown-item">
        <input type="text" id="matriculaInput" name="matricula" v-model="matricula" class="input-field" placeholder="Matrícula">
      </div>
    </div>
    <div class="ord-wrapper" id="designacao">
      <h1>Designação:</h1>
      <div class="dropdown-item">
        <input type="text" id="designacaoInput" name="designacao" v-model="designacao" class="input-field" placeholder="Designação">
      </div>
    </div>
    <div class="ord-wrapper" id="nome">
      <h1>Nome:</h1>
      <div class="dropdown-item">
        <input type="text" id="nomeInput" name="nome" v-model="nome" class="input-field" placeholder="Nome">
      </div>
    </div>
    <div class="ord-wrapper" id="email">
      <h1>Email:</h1>
      <div class="dropdown-item">
        <input type="text" id="emailInput" name="email" v-model="email" class="input-field" placeholder="Email">
      </div>
    </div>
    <div class="ord-wrapper" id="contacto">
      <h1>Contacto:</h1>
      <div class="dropdown-item">
        <input type="text" id="contactoInput" name="contacto" v-model="contacto" class="input-field" placeholder="Contacto">
      </div>
    </div>

    <!-- Botões no canto inferior esquerdo -->
    <div class="button" id="button">
      <button id="clearFiltersButton" :class="{ 'button-clicked': clearButtonClicked, 'button-hovered': isHovered1 }" @click="clearFilters"
                                                                                                                      @mouseover="isHovered1 = true"
                                                                                                                      @mouseout="isHovered1 = false">
        Limpar Filtros</button>
      <button id="searchButton" :class="{ 'button-clicked': searchButtonClicke, 'button-hovered': isHovered2  }" @click="applyFilters" 
                                                                                                                        @mouseover="isHovered2 = true"
                                                                                                                        @mouseout="isHovered2 = false">
        <img src="../assets/Lupa.png" alt="Lupa"> Pesquisar
      </button>
    </div>
  </div>
</template>

<script>
import { useAuthStore } from '../store/authStore';
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
      nome: '',
      email: '',
      contacto: '',
      originalServiceList: [], // Armazenar os serviços originais localmente
      filteredServiceList: [], // Lista de serviços filtrada
      authStore: useAuthStore(),
      veiculos: [],
      clientes: [],
      clearButtonClicked: false,
      searchButtonClicked: false,
      isHovered1: false,
      isHovered2: false
    };
  },
  mounted() {
    this.fetchData();
  },
  methods: {
    async fetchData() {
      try {
        const userServices = this.authStore.user['serviços-realizados'];
        this.originalServiceList = userServices; // Armazenar os serviços originais

        const vehicleResponse = await this.fetchVeiculosData();
        this.veiculos = vehicleResponse.data;

        const clientResponse = await this.fetchClientesData();
        this.clientes = clientResponse.data;

      } catch (error) {
        console.error('Error fetching data on pinia:', error);
      }
    },
    async fetchVeiculosData() {
      const response = await axios.get(`${JSON_SERVER_URL}/vehicles`);
      return response;
    },
    async fetchClientesData() {
      const response = await axios.get(`${JSON_SERVER_URL}/clients/`);
      return response;
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
      return serviceList.filter(service =>
        service.vehicleId.startsWith(matricula)
      );
    },
    filterByDesignacao(serviceList, designacao) {
      return serviceList.filter(service =>
        service.descrição.startsWith(designacao)
      );
    },
    filterByNome(serviceList, nome) {
      return this.filterByClientAttribute(serviceList, 'nome', nome);
    },
    filterByEmail(serviceList, email) {
      return this.filterByClientAttribute(serviceList, 'email', email);
    },
    filterByContacto(serviceList, contacto) {
      return this.filterByClientAttribute(serviceList, 'telefone', contacto);
    },
    filterByClientAttribute(serviceList, attribute, value) {
      return serviceList.filter(service => {
        const veiculo = this.veiculos.find(v => v.id === service.vehicleId);
        if (!veiculo) return false;

        const client = this.clientes.find(c => c.id === veiculo.clientId);
        if (!client) return false;
        
        const attributeValue = client[attribute];

        const startsWith = attributeValue.startsWith(value);

        return startsWith;
      });
    },
    applyFilters() {
      let copia = [...this.originalServiceList]; // copia dos serviços originais

      // Filtrar por serviço realizado
      copia = this.filtraRealizados(copia, "realizado");

      if (this.startDate && this.endDate) {
        copia = this.filterByCustomDate(copia, this.startDate, this.endDate);
      }
      // Filtrar por matrícula
      if (this.matricula !=='') {
        copia = this.filterByMatricula(copia, this.matricula);
      }

      if (this.designacao !=='') {
        copia = this.filterByDesignacao(copia, this.designacao);
      }
      if (this.nome !=='') {
        copia = this.filterByNome(copia, this.nome);
      }
      if (this.email !=='') {
        copia = this.filterByEmail(copia, this.email);
      }

      if (this.contacto !=='') {
        copia = this.filterByContacto(copia, this.contacto);
      }

      // Emitir evento com os serviços filtrados
      this.$emit('filters-applied', copia);
      // Ativar o estado para aplicar a classe CSS
      this.searchButtonClicked = true;

      // Resetar o estado após 300ms
      setTimeout(() => {
        this.searchButtonClicked = false;
      }, 100);
    },
    clearFilters() {
      let copia = [...this.originalServiceList]; // copia dos serviços originais

      // Limpar os campos de filtro
      this.startDate = '';
      this.endDate = '';
      this.matricula = '';
      this.designacao = '';
      this.nome = '',
        this.email = '',
        this.contacto = '',

        // Restaurar a lista original sem filtros
        this.$emit('filters-applied', copia);

      // Ativar o estado para aplicar a classe CSS
      this.clearButtonClicked = true;

      // Resetar o estado após 300ms
      setTimeout(() => {
        this.clearButtonClicked = false;
      }, 100);
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
  grid-template-areas:
    "title . ."
    "data matricula designacao"
    "nome email contacto"
    "button button button";
    grid-template-columns: repeat(auto-fit, minmax(350px, 1fr));
}

#data {
  grid-area: data;
}

#matricula {
  grid-area: matricula;
}

#designacao {
  grid-area: designacao;
}

#nome {
  grid-area: nome;
}

#email {
  grid-area: email;
}

#contacto {
  grid-area: contacto;
}

#title {
  grid-area: title;
}

#button {
  grid-area: button;
}

.Title {
  font-size: 35px;
  font-weight: bold;
  color: #0E3C79;
  margin-top: 40px;
  padding-left: 40px;
}

.ord-wrapper {
  width: 350px;
  display: flex;
  flex-direction: column;
  padding-left: 30px;
}

.ord-wrapper h1 {
  font-size: 18px;
  font-family: 'Inter', sans-serif;
  color: #616161;
  font-weight: normal;
}

.dropdown-item {
  display: flex;
  align-items: center;
  height: 48px;
  background-color: #fff;
  border: 1px solid #000;
  border-radius: 5px;
  padding: 0 10px;
}

.dropdown-item:hover {
  background-color: #f5f5f5;
}

.dropdown-item input::placeholder {
  color: #D2D2D2;
}

.date-section {
  display: flex;
  align-items: center;
}

.date-section input {
  width: 100%;
}

.date-section label {
  padding: 5px;
}

.input-field {
  flex: 1;
  font-size: 14px;
  font-family: 'Inter', sans-serif;
  border: none;
  outline: none;
}

.button {
  width: 100%;
  display: flex;
  align-items: center;
  justify-content: flex-end;
}
.button-hovered {
  box-shadow: 0 3px 6px rgba(0, 0, 0, 0.3);
}

#clearFiltersButton,
#searchButton {
  width: 100%; 
  max-width: 200px;
  height: 45px;
  background-color: #ffffff;
  color: #1E56A0;
  border: 1px solid #1E56A0;
  border-radius: 5px;
  font-size: 18px;
  cursor: pointer;
  font-weight: bold;
  margin: 10px;
}

#searchButton {
  padding-right: 30px;
  position: relative;
}

#searchButton img {
  position: absolute;
  padding: 0 95px;
  width: 20px;
  height: 20px;
}

#clearFiltersButton.button-clicked,
#searchButton.button-clicked {
  background-color: #A3C8FF;
}

#searchButton:hover img {
  mix-blend-mode: multiply;
}

@media (max-width: 1350px) {

  .menus-container {
    background-color: #FFF;
    border-bottom: 1px solid #1E56A0;
    border-left: 0px;
    display: grid;
    grid-template-areas:
    "title . ."
    "data matricula designacao"
    "nome email contacto"
    "button button button";
    grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
  }

  .Title {
    font-size: 30px;
    }

  .ord-wrapper {
    width: 275px;
    padding-left: 20px;
  }

  .ord-wrapper h1 {
    font-size: 16px;
  }

  .dropdown-item {
    height: 44px;
  }

  .date-section {
    font-size: 14px;
  }

  .date-section input {
    width: 33%;
    font-size: 11px;
  }

  .input-field {
    font-size: 14px;
  }

  #clearFiltersButton,
  #searchButton {
    height: 40px;
  }
}


@media (max-width: 1024px) {

  .menus-container {
    background-color: #FFF;
    border-bottom: 1px solid #1E56A0;
    border-left: 0px;
    display: grid;
    grid-template-areas:
    "title . ."
    "data matricula designacao"
    "nome email contacto"
    "button button button";
    grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
  }

  .Title {
    font-size: 20px;
  }

  .ord-wrapper {
    width: 235px;
    padding-left: 10px;
  }

  .ord-wrapper h1 {
    font-size: 16px;
  }

  .dropdown-item {
    height: 40px;
  }

  .date-section input {
    font-size:8px;
  }

  .input-field {
    font-size: 14px;
  }

  #clearFiltersButton,
  #searchButton {
    height: 40px;
  }
}

@media (max-width: 800px){
  .ord-wrapper h1 {
    font-size: 12px;
  }
  .ord-wrapper {
    width: 200px;
    padding-left: 5px;
  }

  .date-section {
    font-size: 12px;
  }
  .dropdown-item {
    height: 40px;
  }

  .date-section input {
    width: 25%;
  }

  .input-field {
    font-size: 12px;
  }

  #clearFiltersButton,
  #searchButton {
    height: 35px;
    width: 30%;
    font-size: 14px;
  }

  .menus-container {
    grid-template-columns: repeat(auto-fit, minmax(33%, 1fr));
  }
}
</style>