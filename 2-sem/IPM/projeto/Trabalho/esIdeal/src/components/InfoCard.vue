<template>
    <div class="fundo">
        <div class="profile">
            <img src="../assets/PersonCircle.png" />
            <p>{{ username }}</p>
        </div>
        <div class="spec">
            <h1>Especialização:</h1>
            <h2>{{ especializacaoDescricao }}</h2>
            <h1>Posto:</h1>
            <h2>{{ posto }}</h2>
        </div>
        <EndSession id="sessao" />
        <div id="historico" class="container-btn">
            <button @click="goHistorico()"
                                  @mouseover="isHovered = true"
                                  @mouseout="isHovered = false"
                                  :class="{ 'button-hovered': isHovered }">
            Histórico de serviços</button>
        </div>
        <div class="filler"></div>
        <div id="clock" class="clock-container">
            {{ currentTime }}
        </div>
    </div>
</template>

<script>

import EndSession from "./EndSession.vue";
import { useAuthStore } from '../store/authStore';
import { useStationStore } from '../store/stationStore';

export default{
    name: "InfoCardComponent",
    components: {
      EndSession
    },
    data() {
    return {
      currentTime: this.getCurrentTime(),
      isHovered: false
    };
  },
  props: {
    stationData: {
      type: Object,
      required: true
    }
  },
  computed: {
    username() {
      const authStore = useAuthStore();
      if (authStore.user) {
        return authStore.user.nome;
      }
    },
    especializacao() {
      const authStore = useAuthStore();
      if (authStore.user) {
        return authStore.user.especialização;
      }
    },
    posto() {
      const stationStore = useStationStore();
      if (stationStore.station) {
        return stationStore.station.nome;
      }
    },
    especializacaoDescricao() {
      const authStore = useAuthStore();
      if (authStore.user) {
        const especialidade = authStore.user.especialização
        if (especialidade === 'geral') {
          return 'Todo o tipo de veículos';
        } else if (especialidade === 'combustao') {
          return 'Motores a combustão';
        } else if (especialidade === 'eletrico') {
          return 'Motores elétricos';
        } else {
          return 'Especialização não especificada';
        }
      }
    }
  },
  methods: {
    getCurrentTime() {
      const date = new Date();
      const hours = String(date.getHours()).padStart(2, '0');
      const minutes = String(date.getMinutes()).padStart(2, '0');
      return `${hours}:${minutes}`;
    },
    goHistorico(){
      this.$router.push("/history")
    },
    updateTime() {
      this.currentTime = this.getCurrentTime();
    }
  },
  mounted() {
    // Update time every second
    this.timer = setInterval(() => {
      this.updateTime();
    }, 1000);
  },
  beforeUnmount() {
    // Clear the interval when the component is destroyed
    clearInterval(this.timer);
  }
};
</script>
<style scoped>

.fundo {
    background-color: #B7D6FF;
    border-right: 1px solid #1E56A0;
    height: 100%;
    display: grid;
    grid-template-rows: 218px 176px auto auto 242px 194px;
    grid-template-columns: 100%;
    gap: 0px;
    grid-template-areas:
        "profile"
        "spec"
        "sessao"
        "historico"
        "filler"
        "clock";

}
.profile{
    background-color:  #B7D6FF;
    grid-area: profile;
    width: 100%;
    height: 100%;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
}
.profile img {
    margin-top: 90px;

}

.profile p {
    color: #000000;
    font-size: 20px;
    font-family: 'Inter', sans-serif;
    font-weight: normal;
}

.spec{

    background-color:  #B7D6FF;
    grid-area: spec;
    width: 100%;
    height: 100%;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;

}

.spec h1{

    font-size: 20px;
    margin-bottom: 5px;
    font-weight: bold;
    color: #0E3C79;
    font-family: 'Inter', sans-serif;

}

.spec h2{

    font-size: 20px;
    margin-bottom: 5px;
    margin-top: 3px;
    font-weight: normal;
    color:#0E3C79;
    font-family: 'Inter', sans-serif;

}
#sessao{
    grid-area: sessao;
}

.container-btn{
    background-color:  #B7D6FF;
    width: 100%;
    height: 100%;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
}
.button-hovered {
  box-shadow: 0 3px 6px rgba(0, 0, 0, 0.3);
}


.container-btn button{
  width: 60%;
  height: 60px;
  background-color: #1E56A0;
  color: white;
  border: none;
  border-radius: 4px;
  font-size: 14px;
  cursor: pointer;
  font-family: "Lato", sans-serif;
  font-weight: bold;
  padding: 10px 20px;
}

.filler {
    grid-area: filler;
    background-color:  #B7D6FF;
    width: 100%;
    height: 100%;

}

.clock-container {
    font-family: 'Inter', sans-serif;
    grid-area: clock;
    background-color:  #B7D6FF;
    width: 100%;
    height: 100%;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    font-size: 40px;
    color: #0E3C79;
}

@media (max-width: 1350px) {
    .profile img {
        margin-top: 50px;
    }
    .profile p {
        font-size: 18px;
    }
    .spec h1{
        font-size: 18px;
    }
    .spec h2{
        font-size: 16px;
    }
    .container-btn button{
        width: 60%;
        height: 60px;
        font-size: 12px;
    }
    .clock-container {
        font-size: 30px;
    }

}


@media (max-width: 1024px) {
  .profile img {
    margin-top: 20px;
  }
  .profile p {
    font-size: 16px;
  }
  .spec h1{
    font-size: 16px;
  }
  .spec h2{
    font-size: 14px;
  }
  .container-btn button{
    width: 60%;
    height: 60px;
    font-size: 10px;
  }
  .clock-container {
    font-size: 25px;
  }

}



@media (max-width: 800px) {
  .fundo {
    grid-template-columns: 88px 230px auto auto 154px;
    grid-template-rows: 50% 50%;
    gap: 0px;
    grid-template-areas:
        "profile spec sessao filler clock"
        "profile spec historico filler clock";
    overflow: auto;
  }
  .profile img{
    margin-top: 0px;
  }

  .container-btn{
    display: grid;
    place-items: center;
  }

  .container-btn button{
    width: 70%;
    height: 60px;
    font-size: 10px;
    margin-bottom: 10px;
  }

  .clock-container {
    font-size: 25px;
  }

}
</style>