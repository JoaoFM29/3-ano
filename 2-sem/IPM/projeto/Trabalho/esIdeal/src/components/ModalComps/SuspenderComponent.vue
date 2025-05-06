<template>
    <div class="form-container">
        <form>
            <div id ="mot">
            <h1>Motivo:</h1>
            <input v-model="motivacao" class="motivo" />
            </div>
            <div id="des">
            <h1>Descrição:</h1>
            <input v-model="descricao" class="desc"/>
            </div>
            <div id="susp">
            <button @click="sendData" :style="buttonStyle" :disabled="isButtonDisabled" type="submit">Suspender</button>
            </div>
        </form>
    </div>
</template>

<script>

const JSON_SERVER_URL = 'http://localhost:3000';
import axios from 'axios';
import { useStationStore } from '@/store/stationStore';


export default {
    name: 'SuspenderComponent',
    data() {
      return {
          motivacao: '',
          descricao: ''
      };
    },
    computed: {
      buttonStyle() {
          return {
              backgroundColor: this.isFormFilled ? '#1E56A0' : '#6BABFF',
              cursor: this.isFormFilled ? 'pointer' : 'not-allowed'
          };
      },
      isFormFilled() {
          return this.motivacao.trim() !== '' && this.descricao.trim() !== '';
      },
      isButtonDisabled() {
          return !this.isFormFilled;
      }
  },
    props: {
    serviceData: {
      type: Object,
      required: true,
    },
  }, methods: {
        sendData() {
            this.serviceData.estado ='parado';
            const updatedServiceData = {
                ...this.serviceData,
                'motivacao': this.motivacao,
                'descricao': this.descricao,
            };
            const stationData = useStationStore();
            delete updatedServiceData.descr;
            delete updatedServiceData.duração;
            axios.put(`${JSON_SERVER_URL}/services/` + updatedServiceData.id, updatedServiceData);
            this.$router.push({ name: 'home', params: { stationID: stationData.station.id } });

        },
  }
}
</script>


<style scope>
.form-container{
    height: 100%;
    width: 100%;
}
form{
    height: 100%;
    width: 100%;
    display: grid;
    grid-template-rows: 39px 125px 274px 81px ;
    grid-template-columns: 100%;
    gap: 0px;
    grid-template-areas:
        "."
        "mot"
        "des"
        "susp";
}
#mot{
    grid-area: mot;
    display: flex;
    justify-content: center;
    flex-direction: column;
}
#des{
    grid-area: des;
    display: flex;
    justify-content: center;
    flex-direction: column;
}
#susp{
    grid-area: susp;
    display: flex;
    justify-content: center;
    flex-direction: column;
}
.motivo{
    border-width: 1px;
    height:55px;
    width:95%;
    border-radius: 5px;
    text-indent: 5px;
    align-self: center;
    
}
.form-container h1{
    text-indent: 20px;
    font-weight: bold;
    font-size: 18px;
    font-family: 'Inter',sans-serif;
    color:rgb(14, 60, 121,0.75);

}
.desc{
    border-width: 1px;
    padding-top:5px;
    padding-bottom:216px;
    text-indent: 5px;
    width:95%;
    border-radius: 5px;
    align-self: center;
    text-align: left;
}

.form-container button{
    width: 135px;
    height:46px;
    align-self: center;  

    color: white;
    border: none;
    border-radius: 4px;
    font-size: 14px;
    cursor: pointer;
    box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1);
    font-family: "Lato", sans-serif;
    font-weight: bold;
    padding: 10px 20px;
    display: flex;
    justify-content: center;
    align-items: center;

}

@media (max-width: 1024px) {
  form {
    grid-template-rows: 19px 125px 244px 101px;
  }
}


@media (max-width: 900px) {
  .motivo{
    height:40px;
  }

  form {
    grid-template-rows: 1px 115px 200px 41px;
  }

  .form-container button{
    width: 105px;
    height:26px;
    font-size: 12px;
  }

  .form-container h1{
    font-size: 16px;
  }

  .desc{
    padding-bottom: 120px;
  }
}

@media (max-width: 700px) {
  .motivo{
    height:20px;
  }

  .desc{
    padding-bottom: 120px;
  }

  form {
    grid-template-rows: 0px 50px 200px 20px;
  }

  .form-container button{
    width: 105px;
    height:26px;
    font-size: 12px;
  }
  .form-container h1{
    font-size: 12px;
  }
}

</style>