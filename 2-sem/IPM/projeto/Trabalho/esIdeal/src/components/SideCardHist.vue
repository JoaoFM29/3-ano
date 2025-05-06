<template>
    <div class="fundo">
        <div class="top" id ="title" >
            <h1>Histórico da E.S.Ideal</h1>
        </div>
        <GoBackButton2 id="go-back-menu" />
        <EndSession id="sessao" />
        <div class="filler"></div>
        <div id="clock" class="clock-container">
            <h1>{{ currentTime }}</h1>
        </div>
    </div>
</template>

<script>
import GoBackButton2 from "../components/GoBackButton2.vue";
import EndSession from "./EndSession.vue";

export default{
    name: "SideCardHistComponent",
    components: {
      GoBackButton2,
      EndSession
    },
    data() {
    return {
      currentTime: this.getCurrentTime()
    };
  },
  methods: {
    getCurrentTime() {
      const date = new Date();
      const hours = String(date.getHours()).padStart(2, '0');
      const minutes = String(date.getMinutes()).padStart(2, '0');
      return `${hours}:${minutes}`;
    },
    updateTime() {
      this.currentTime = this.getCurrentTime();
    },
    goBack() {
        this.$router.push({ name: 'home' });
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
    height: 100%;
    display: grid;
    grid-template-rows: 232px 96px 96px 410px 190px;
    grid-template-columns: 100%;
    gap: 0px;
    grid-template-areas:
        "title"
        "go-back-menu"
        "sessao"
        "filler"
        "clock";
    
}

#sessao{
    grid-area: sessao;
    border-right: 1px solid #1E56A0;
}

#go-back-menu{
    grid-area: go-back-menu;
    border-right: 1px solid #1E56A0;
}

#title{
    grid-area: title;
    border-right: 1px solid #1E56A0;
}

.top {

    background-color:  #B7D6FF;
    width: 100%;
    height: 100%;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;


}

.top h1{
    font-family: 'Inter', sans-serif;
    text-align: center;
    font-weight: bolder;
    font-size: 25px;
    color: #1E56A0;
    width: 80%;
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

.container-btn button{

  width: 50%;
  height: 60px;
  background-color: #1E56A0;
  color: white;
  border: none;
  border-radius: 4px;
  font-size: 14px;
  cursor: pointer;
  box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.1);
  font-family: "Lato", sans-serif;
  font-weight: bold;
  padding: 10px 20px;

}


.container-btn2{
    background-color:  #B7D6FF;
    width: 100%;
    height: 100%;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
}

.container-btn2 button{

  width: 50%;
  height: 46px;
  background-color: #1E56A0;
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
  flex-direction: line;
  justify-content: space-evenly;
  align-items: center;

}

.filler {
    grid-area: filler;
    background-color:  #B7D6FF;
    width: 100%;
    height: 100%;
    border-right: 1px solid #1E56A0;

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
    border-right: 1px solid #1E56A0;
}

.clock-container h1{
    font-family: 'Inter', sans-serif;
    font-size: 40px;
    font-weight: normal;
    color: #0E3C79;
    margin-bottom: 100px;
}

@media (max-width: 1024px) {

  .top h1 {
    font-size: 20px;
  }

}



@media (max-width: 800px) {
  .fundo {
    grid-template-columns: 250px 200px auto 200px;
    grid-template-rows: 50% 50%;
    gap: 0px;
    grid-template-areas:
        "title go-back-menu filler clock"
        "title sessao filler clock";

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
    font-size: 20213px;
  }

  #sessao{
    border-right: 0px;
  }

  #go-back-menu{
    border-right: 0px;
  }

  #title{
    border-right: 0px;
  }

  .filler {
    border-right: 0px;
  }

  .clock-container {
    border-right: 0px;
  }
  .clock-container h1{
    font-size: 25px;
    margin-bottom: 0px;

  }
}
</style>
