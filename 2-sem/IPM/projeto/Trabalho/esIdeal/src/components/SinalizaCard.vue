<template>
  <div class="menu-container">
      <div class="card">
          <div class="title">
              <h1>Sinalizar Serviço</h1>
          </div>
          <div id="btn-a">
              <button @click="handleBtnAClick"        
                          @mouseover="isHovered1 = true"
                          @mouseout="isHovered1 = false"
                          :class="{ 'button-hovered': isHovered1 }">
                  <h1>{{ btnAText }}</h1>
              </button>
          </div>
          <div id="btn-b">
              <button @click="handleBtnBClick" :style="buttonStyle" :disabled="!isBtnBClickable"                         
                                      @mouseover="isHovered2 = true"
                                      @mouseout="isHovered2 = false"
                                      :class="{ 'button-hovered': isHovered2 && isBtnBClickable }">
                  <h1> {{ btnBText }} </h1>
              </button>
          </div>
      </div>
  </div>
</template>

<script>


export default {
name: 'SinalizaCard',
data() {
  return {
    isHovered1: false,
    isHovered2: false
  }
},
props: {
  serviceData: {
    type: Object,
    required: true,
  },
},
emits: ['mudarServicoEsq','mudarServicoDir'],
computed: {
  isBtnBClickable() {
  const clickable = this.serviceData.estado === 'aDecorrer' || this.serviceData.estado === 'parado';
  return clickable;
},
  btnAText() {
    switch (this.serviceData.estado) {
      case 'aDecorrer':
        return 'Terminar Serviço';
      case 'parado':
        return 'Cancelar Serviço';
      default:
        return 'Começar Serviço';
    }
    
  },
  btnBText() {
    switch (this.serviceData.estado) {
      case 'aDecorrer':
        return 'Suspender Serviço';
      case 'parado':
        return 'Continuar Serviço';
      default:
        return 'Suspender Serviço';
    }
    
  },
  buttonStyle() {
          return {
              backgroundColor: this.isBtnBClickable ? '#1E56A0' : '#6BABFF',
              cursor: this.isBtnBClickable ? 'pointer' : 'not-allowed'
          };
      },
  },
  methods: {
    handleBtnAClick() {
      this.$emit('mudarServicoEsq',this.serviceData);
    },
    handleBtnBClick() {
      this.$emit('mudarServicoDir',this.serviceData);
    },
    
  },
};
</script>

<style scoped>

.menu-container{
    width: 100%;
    height: 100%;
    display: flex;
    justify-content: center;
    align-items: center;
    
}

.menu-container .card{
    width: 771px;
    height: 252px;
    border-radius: 20px;
    background-color: #B7D6FF;
    display: grid;
    grid-template-rows: 74px 178px;
    grid-template-columns: 5% 45% 45% 4%;
    gap: 3px;
    border-color: #1E56A0;
    border-style: solid;
    border-width: 1px;
    grid-template-areas:
        "title title title title"
        ". btn-a btn-b .";
    margin-bottom: 80px;
}

#btn-a{
    grid-area: btn-a;
    display: flex;
    justify-content: center;
    align-items: center;
}
.button-hovered {
  box-shadow: 0 3px 6px rgba(0, 0, 0, 0.3);
}

#btn-b{
    grid-area: btn-b;
    display: flex;
    justify-content: center;
    align-items: center;
}

.menu-container .card button{
    height: 50%;
    width: 65%;
    align-self: center;   
    background-color: #1E56A0;
    color: white;
    border: none;
    border-radius: 4px;
    font-size: 18px;
    cursor: pointer;
    font-family: "Lato", sans-serif;
    font-weight: bold;
    padding: 10px 20px;
    display: flex;
    justify-content: center;
    align-items: center;

    
}

.menu-container .card button h1{
    font-family: "Lato", sans-serif;
    width: 80%;
    font-weight: bold;
    font-size: 18px;
    color: white;
    
}

.title {
    grid-area: title;
    width: 99.8%;
    height: 100%;
    border-radius: 20px;
    background-color: #8BBDFF;
    border-color: #1E56A0;
    border-style: solid;
    border-width: 1px;
    display: flex;
    flex-direction: row;
    justify-content: center;
    align-items: center;
    margin-top: -1px;
    
}
.title h1{
    width: 64%; 
    text-align: center;
    font-size: 20px;
    font-family: "Lato", sans-serif;
    font-weight: bold;
    color: #000;
    
}


@media (max-width: 1024px) {
  .menu-container .card{
    width: 90%;
    height: 70%;
  }

  .title h1{
    font-size: 18px;
  }
  .menu-container .card button{
    margin-top: -2rem;
    height: 40%;
    width: 60%;

  }
  .menu-container .card button h1{
    font-size: 16px;
  }

  .element h1{
    font-size: 16px;
  }
  .element h2{
    font-size: 16px;
    text-align: center;
  }

}

@media (max-width: 800px) {
  .menu-container .card{
    width: 90%;
    height: 70%;
  }

  .title h1{
    font-size: 18px;
  }
  .menu-container .card button{
    margin-top: -2rem;
    height: 30%;
    width: 80%;

  }
  .menu-container .card button h1{
    font-size: 12px;
  }

  .element h1{
    font-size: 12px;
  }
  .element h2{
    font-size: 12px;
    text-align: center;
  }

}

</style>