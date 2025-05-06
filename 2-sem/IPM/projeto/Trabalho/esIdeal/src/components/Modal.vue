<template>
    <div class="vue-modal" v-show="open">
        <transition name="slide">
          <div class="veu-modal-inner">
            
            <div class="vue-modal-content">
              <button type="button" @click="$emit('close')"><img src="../assets/ArrowLeftCircleFill.png" />
                <h1>Voltar</h1></button>
              
              <div class="card">
                <div class="title">
                  <h1>{{titulo}}</h1>
              </div>
              <slot /> 
            </div>     
            </div>
          </div>
        </transition>
      </div>
  </template>
  
  <script>
  export default {
    props: {
      open: {
        type: Boolean,
        default: true,
      },
      titulo: {
        type: String,
        default: "Terminar Serviço"
      }
    },
  };
  </script>
<style scoped>

*,
::before,
::after {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

.vue-modal {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  overflow-x: hidden;
  overflow-y: auto;
  background-color: rgba(0, 0, 0, 0.4);
  z-index: 1;
  display: flex;
  justify-content: center; 
  align-items: center;     
}

.vue-modal-inner {
  background-color: #fff;
  border: 1px solid rgba(0, 0, 0, 0.3);
  background-clip: padding-box;
  border-radius: 0.3rem;
  flex-direction: column;
  justify-content: center;   
}

.vue-modal-content {
  position: relative;
  background-color: #fff;
  border: 1px solid rgba(0, 0, 0, 0.3);
  background-clip: padding-box;
  border-radius: 0.3rem;
  padding: 1rem;
  width: 970px;
  height: 780px;
  display: flex;
  flex-direction: column;
  justify-content: center; 

}

.card{
  width: 907px;
  height: 599px;
  border-radius: 20px;
  background-color: #B7D6FF;
  border-color: #1E56A0;
  border-style: solid;
  border-width: 1px;
  display: flex;
  flex-direction: column;
  align-self: center;
  
}
button {

  width: 160px;
  height: 66px;
  border-radius: 20px;
  background-color: #B7D6FF;
  border-style:  solid;
  border-color: #1E56A0;
  border-width: 1px;
  align-self: left;
  margin-left: 25px;
  margin-bottom: 25px;
  display: flex;
  cursor: pointer;
  flex-direction: row;
  justify-content: center;
  align-items: center;
}

button img {
  margin-right: 10px;
}

button h1 {
  font-size: 20px;
  font-family: "Lato", sans-serif;
  font-weight: bold;
  color: #0E3C79;
}

.title {
  grid-area: title;
  width: 100%;
  height: 80px;
  border-radius: 20px;
  background-color: #8BBDFF;
  border-color: #1E56A0;
  border-width: 1px;
  border-style: solid;
  display: flex;
  flex-direction: row;
  justify-content: center;
  align-items: center;
  
}
.title h1{
  width: 30%;
  text-align: center;
  font-size: 20px;
  font-family: "Lato", sans-serif;
  font-weight: bold;
  color: #000;
  
}

@media (max-width: 1024px) {
  .vue-modal-content {
    width: 870px;
    height: 700px;
  }
  .card {
    width: 813px;
    height: 540px;
  }
  button {
    width: 120px;
    height: 50px;
  }
  button h1 {
    font-size: 18px;
  }
  .title h1{
    font-size: 18px;
  }
}

@media (max-width: 900px) {
  .vue-modal-content {
    width: 700px;
    height: 563px;
  }
  .card {
    width: 654px;
    height: 434px;
  }
  button {
    width: 120px;
    height: 50px;
  }
  button h1 {
    font-size: 16px;
  }
  .title h1{
    font-size: 16px;
  }
}

@media (max-width: 700px) {
  .vue-modal-content {
    width: 600px;
    height: 483px;
  }
  .card {
    width: 560px;
    height: 372px;
  }
  button {
    width: 110px;
    height: 40px;
  }
  button h1 {
    font-size: 16px;
  }
  .title h1{
    font-size: 14px;
  }
}

</style>