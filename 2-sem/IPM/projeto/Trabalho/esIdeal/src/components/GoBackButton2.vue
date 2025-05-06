<template>
    <div class="container">
        <button @click="goBack()"
                            @mouseover="isHovered = true"
                            @mouseout="isHovered = false"
                            :class="{ 'button-hovered': isHovered }">
            <img src="../assets/back.png" />
            <h1>Voltar</h1>
        </button>
    </div>
</template>

<script>
import { useStationStore } from '../store/stationStore';

export default {
  name: 'GoBackButton2',
  data () {
      return {
        isHovered: false
      }
  },
  methods:{
    goBack(){
      const stationData = useStationStore();
        this.$router.push("/home/" +  stationData.station.id);
    }
  }
}
</script>

<style scoped>
.container{
    width: 100%;
    height: 100%;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
}

.container button{
  width: 50%;
  height: 40px;
  background-color: #1E56A0;
  border: none;
  border-radius: 4px;
  cursor: pointer;
  display: flex;
  flex-direction: line;
  justify-content: space-evenly;
  align-items: center;
}
.button-hovered {
  box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.3);
}

.container button img {
    width: 30px;
}

.container button h1 {
  font-size: 14px;
  font-family: "Lato", sans-serif;
  font-weight: bold;
  color: white;
}
</style>