<template>
    <div class="station-list-container">
      <div class="station-list" v-virtual-scroll="stationData">
        <StationCard v-for="(station, index) in stationData" :key="index" :station="station"/>
      </div>
    </div>
  </template>
  
  <script>
  import StationCard from './StationCard.vue';
  
  export default {
    name: 'StationListComponent',
    props: {
      stationData: {
        type: Array,
        required: true
      }
    },
    components: {
      StationCard
    }
  };
  </script>
  
  <style scoped>
  .station-list-container {
    height: 100%; 
    margin-left: 50px;
    margin-top: 30px;
    overflow-y: scroll;
    overflow-x: hidden;
    width: 982px;
    padding-right: 50px;
  }
  
  .station-list-container::-webkit-scrollbar {
    width: 30px;
  }
  
  .station-list-container::-webkit-scrollbar-track {
    margin-left: 200px;
    background-color: #F1F0F0;
    border-radius: 20px;
  }
  
  .station-list-container::-webkit-scrollbar-thumb {
    background-color: #B5B5B5;
    border-radius: 20px;
  }
  
  .station-list {
    width: 100%;
  }

  @media (max-width: 1350px) {
    .station-list-container {
      margin-left: 20px;
      margin-top: 20px;
      width: 900px;
      padding-right: 30px;
    }
  }

  @media (max-width: 1200px) {
    .station-list-container {
      margin-left: 10px;
      margin-top: 20px;
      width: 800px;
      padding-right: 10px;
    }
  }


  @media (max-width: 1024px) {
    .station-list-container {
      margin-left: 20px;
      margin-top: 20px;
      width: 750px;
      padding-right: 10px;
    }
  }

  @media (max-width: 800px) {
    .station-list-container {
      margin-left: 20px;
      margin-top: 20px;
      width: 700px;
      padding-right: 10px;
    }

    .station-list-container::-webkit-scrollbar {
      width: 15px;
    }
  }

  @media (max-width: 700px) {
    .station-list-container {
      margin-left: 20px;
      margin-top: 20px;
      width: 600px;
      padding-right: 10px;
    }

    .station-list-container::-webkit-scrollbar {
      width: 15px;
    }
  }
  </style>
  
  