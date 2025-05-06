<template>
    <div class="container">
        <button @click="goBack()"
                          @mouseover="isHovered = true"
                          @mouseout="isHovered = false"
                          :class="{ 'button-hovered': isHovered }">
            <img src="../assets/ArrowLeftCircleFill.png" />
            <h1>Serviços Atribuídos</h1>
        </button>
    </div>
</template>

<script>
import { useStationStore } from '../store/stationStore';
import { useFromStore } from '../store/fromStore';

export default {
  name: 'GoBackButton',
  data() {
    return {
      isHovered: false,
      fromStore: useFromStore(),
    } 
  },
  methods:{
    goBack(){
      if(this.fromStore.from){
        const stationData = useStationStore();
        this.$router.push("/home/" +  stationData.station.id);
      }
      else {
        this.$router.push({ name : "history"});
      }

    }
  }
}
</script>

<style scoped>
.container{
    width: 100%;
    height: 100%;
    display: flex;
    flex-direction: row;
    justify-content: center;
    align-items: center;
}

.container button{
  width: 312px;
  height: 66px;
  background-color: #B7D6FF;
  color: #0E3C79;
  border-color: #1E56A0;
  border-style: solid;
  border-width: 1px;
  border-radius: 20px;
  font-size: 20px;
  cursor: pointer;
  padding: 10px 20px;
  margin-left: 0px;
  display: flex;
  flex-direction: row;
  justify-content: center;
  align-items: center;
}
.button-hovered {
  box-shadow: 0 3px 6px rgba(0, 0, 0, 0.3);
}


.container button img {
    margin-right: 10px;
}

.container button h1 {
    font-size: 20px;
    font-family: "Lato", sans-serif;
    font-weight: bold;
    color: #0E3C79;
}

@media (max-width: 1024px) {
  .container button {
    width: 284px;
    height: 60px;
  }
  .container button h1 {
    font-size: 18px;
  }
}
</style>