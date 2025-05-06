<template>
    <div class="menus-container">
      <div class="ord-wrapper" id="ordenacao">
      </div>
    </div>
  </template>
  
  <script>
  export default {
    name: 'FormMenuBar',
    data() {
      return {
      }
    },
   
  }
  </script>
  
  <style scoped>
  .menus-container {
    background-color: #FFF;
    border-bottom: 1px solid #1E56A0;
    border-left: 0px;
    display: grid;
    grid-template-rows: 100%;
    grid-template-columns: 33.3% 33.3% 33.3%;
    gap: 0px;
    grid-template-areas: "ordenacao estado agendamento";
  }
  
  .ord-wrapper {
    display: flex;
    justify-content: center;
    align-items: center;
    flex-direction: column;
  }
  
  .ord-wrapper h1 {
    font-size: 16px;
    font-family: 'Inter',sans-serif;
    color: #616161;
    font-weight: normal;
    align-self: flex-start;
    margin-left: 38px;
  }
  
  
  #ordenacao {
    grid-area: ordenacao;
  }
  #estado {
    grid-area: estado;
  }
  #agendamento {
    grid-area: agendamento;
  }
  
  .down-wrapper {
    margin-top: 0px;
  }
  </style>
  