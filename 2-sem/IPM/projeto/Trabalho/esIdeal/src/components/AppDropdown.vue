<template>
    <div @click="toggle" class="dropdown-container">
      <div name="toggler">
        <button>
          <div class="button-content">
            <slot name="button"/>
            <img v-if="sharedState.active" id="rodada" src="../assets/Polygon.png" alt="Polygon Icon">
            <img v-else src="../assets/Polygon.png" alt="Polygon Icon">
          </div>
        </button>
      </div>
      <div v-if="sharedState.active" class="dropdown-content">
        <slot name="dropdown"/>
      </div>
    </div>
  </template>
  
  <style scoped>
  button {
    display: flex;
    align-items: center;
    justify-content: center;
    width: 320px;
    height: 44px;
    background-color: #fff;
    border-style: solid;
    border-width: 1px;
    border-color: #000;
    font-size: 16px;
    font-family: 'Inter', sans-serif;
  }
  
  .button-content {
    display: flex;
    align-items: center;
    justify-content: space-between;
    width: 90%;
  }
  
  .dropdown-container {
    position: relative;
  }
  
  .dropdown-content {
    position: absolute;
    top: 100%;
    left: 0;
    width: 100%;
    z-index: 1;
  }

  #rodada {

    transform: rotate(180deg);
  }

  @media (max-width: 1350px) {
    button {
      width: 238px;
    }
  }

  @media (max-width: 1024px) {
    button {
      width: 180px;
    }
  }

  @media (max-width: 800px) {
    button {
      font-size: 12px;
      width: 150px;
    }
  }
  </style>
  
  
  <script>
  export default {
    name: 'AppDropdown',
    provide() {
      return {
        sharedState: this.sharedState
      }
    },
    data() {
      return {
        sharedState: {
          active: false
        }
      }
    },
    methods: {
      toggle() {
        this.sharedState.active = !this.sharedState.active;
      }
    }
  }
  </script>
  