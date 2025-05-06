<template>
  <div class="end-container">
    <div class="check-container">
      <input type="checkbox" value="check" name="check-box" class="check-box" v-model="check" />
      <h1>Adicionar Recomendação</h1>
    </div>
    <div v-if="check" class="list-container">
      <div class="smallcard" v-for="(serv, index) in servicosPossiveis" :key="index">
        <div class="grupo">
          <h1>Designação</h1>
          <h2>{{ serv.descr }}</h2>
        </div>
        <div class="segundo-grupo">
          <input type="checkbox" class="check-box" v-model="serv.checked" />
          <h1>Selecionar</h1>
        </div>
      </div>
    </div>
    <div v-if="check" class="motive-container">
      <h1>Motivo:</h1>
      <input v-model="motivo" class="motivo-form" :style="motivoStyle" :disabled="isMotivoDisabled" />
      <button @click="sendData" :style="buttonStyle" :disabled="isButtonDisabled" type="submit">Terminar</button>
    </div>
    <div v-else class="motive-container">
      <h1>Motivo:</h1>
      <input v-model="motivo" class="motivo-form" :style="motivoStyle" :disabled="isMotivoDisabled" />
      <button @click="sendData" style="cursor: pointer;" type="submit">Terminar</button>
    </div>

  </div>
</template>

<script>
import axios from 'axios';
import { useAuthStore } from '@/store/authStore';
import { useStationStore } from '@/store/stationStore';

export default {
  name: 'TerminarComponent',
  props: {
    serviceData: {
      type: Object,
      required: true,
    },
    servicosPossiveis: {
      type: Array,
      required: true,
    },
  },
  data() {
    return {
      check: false,
      motivo: '',
    };
  },
  computed: {
    checkedItems() {
      return this.servicosPossiveis.some(serv => serv.checked);
    },
    isMotivoDisabled() {
      return !this.checkedItems;
    },
    motivoStyle() {
      return {
        opacity: this.checkedItems ? 1 : 0.9,
      };
    },
    buttonStyle() {
      return {
        backgroundColor: this.isFormFilled ? '#1E56A0' : '#6BABFF',
        cursor: this.isFormFilled ? 'pointer' : 'not-allowed',
      };
    },
    isFormFilled() {
      return this.motivo.trim() !== '';
    },
    isButtonDisabled() {
      return !this.isFormFilled;
    },
  },
  methods: {
    sendData() {
      const sugestoes = this.servicosPossiveis.filter(serv => serv.checked).map(i => i.id);
      const updatedServiceData = {
        ...this.serviceData,
        'estado': 'realizado',
        'motivo-sugestao': this.motivo,
        'sugestoes': sugestoes,
      };
      delete updatedServiceData.descr;
      delete updatedServiceData.duração;
      axios.put(`http://localhost:3000/services/${updatedServiceData.id}`, updatedServiceData);

      const stationData = useStationStore();
      const userData = useAuthStore();
      userData.addService(updatedServiceData);

      axios.put(`http://localhost:3000/mechanics/${userData.user.id}`, userData.user);

      this.$router.push({ name: 'home', params: { stationID: stationData.station.id } });
    },
  },
};
</script>

<style scope>

.end-container{
    height: 100%;
    width: 100%;
    display: grid;
    grid-template-rows: 90px 236px 193px;
    grid-template-columns: 100%;
    gap: 0px;
    grid-template-areas:
        "check-container"
        "lista"
        "motivo-area";
}

.check-container{

    grid-area: check-container;
    height: 100%;
    width: 100%;
    display: flex;
    justify-content: left;
    align-items: center;
    flex-direction: row;
    text-indent: 0px;
    gap:5px

}

.end-container .check-box{
    width: 18px;
    height: 18px;
    margin-left:20px;
    border-radius: 5px;
    cursor: pointer;
    
}
.check-container h1{
    font-size: 16px;
    font-weight: normal;
    color: black;
    font-family:'Inter',sans-serif;
    
}

.list-container {
    position: relative;
    left: 20px;
    grid-area: lista;
    height: 85%; 
    overflow-y: scroll;
    overflow-x: hidden;
    width: 95%;
    padding-right: 0px;
  }
  
  .list-container::-webkit-scrollbar {
    width: 15px;
  }
  
  .list-container::-webkit-scrollbar-track {
    margin-left: 0px;
    background-color: #F1F0F0;
    border-radius: 20px;
  }
  
  .list-container::-webkit-scrollbar-thumb {
    background-color: #B5B5B5;
    border-radius: 20px;
  }

  .list-container .smallcard{
    height: 70px;
    background-color: #fff;
    border-style: solid;
    border-width: 1px;
    width:97%;
    display: flex;
    flex-direction: row;
    justify-content: space-between;

  }

  .grupo{
    text-indent: 10px;
    
  }
  .grupo h1{
    font-size: 20px;
    margin-bottom: -15px;
    font-family: 'Inter',sans-serif;
    color: #6F6A6A;
    font-weight: normal;
  }
  .grupo h2{
    font-size: 20px;
    font-family: 'Inter',sans-serif;
    color: #000;
    font-weight: normal;
  }
  .segundo-grupo{
    display: flex;
    flex-direction: row;
    justify-content: center;
    align-items: center;
    gap:10px;
    margin-right: 20px;
  }
  .segundo-grupo h1{

    font-size: 20px;
    font-family: 'Inter',sans-serif;
    color: #000;
    font-weight: normal;
    

  }
  .motive-container{
    grid-area: motivo-area;
    height: 100%;
    width: 100%;
    display: flex;
    justify-content: center;
    align-items: left;
    flex-direction: column;
    
    
    gap:10px;
  }
  .motive-container h1{
    text-indent: 30px;
    font-weight: bold;
    font-size: 18px;
    font-family: 'Inter',sans-serif;
    color:rgb(14, 60, 121,0.75);
  }
  .motive-container button{
    font-weight: bold;
    font-size: 14px;
    font-family: 'Lato', sans-serif;
    color: white;
    width: 135px;
    height: 46px;
    align-self: center;
    background-color: #1E56A0;
    border: none;
    border-radius: 5px;
    cursor: pointer;
  }
  .motivo-form{
    border-width: 1px;
    height:55px;
    width:95%;
    border-radius: 5px;
    text-indent: 5px;
    align-self: center;
    
}

@media (max-width: 1024px) {
  .end-container {
    grid-template-rows: 50px 220px 203px;
  }
  .grupo h1{
    font-size: 18px;
  }
  .grupo h2 {
    font-size: 18px;
  }
  .segundo-grupo h1{
    font-size: 18px;
  }
  .motive-container h1{
    font-size: 18px;
  }
  .motivo-form{
    height: 50px;
  }

}

@media (max-width: 900px) {
  .end-container {
    grid-template-rows: 40px 190px 130px;
  }
  .grupo h1{
    font-size: 16px;
  }
  .grupo h2 {
    font-size: 16px;
  }
  .segundo-grupo h1{
    font-size: 16px;
  }
  .motive-container h1{
    font-size: 16px;
  }
  .motivo-form{
    height: 40px;
  }

}

@media (max-width: 700px) {
  .end-container {
    grid-template-rows: 40px 150px 80px;
  }
  .grupo h1{
    font-size: 14px;
  }
  .grupo h2 {
    font-size: 14px;
  }
  .motive-container{
    gap:5px;
  }
  .segundo-grupo h1{
    font-size: 14px;
  }
  .motive-container h1{
    font-size: 14px;
  }
  .motivo-form{
    height: 35px;
  }

}

</style>