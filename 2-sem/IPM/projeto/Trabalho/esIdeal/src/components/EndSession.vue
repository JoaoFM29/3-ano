<template>
  <div class="container">
    <button @click="goBack"
            @mouseover="isHovered = true"
            @mouseout="isHovered = false"
            :class="{ 'button-hovered': isHovered }">
      <h1>Terminar Sessão</h1>
    </button>
  </div>
</template>

<script>
import { useStationStore } from '../store/stationStore';
import { useAuthStore } from '../store/authStore';

export default {
  name: 'EndSession',
  data() {
    return {
      isHovered: false
    };
  },
  methods: {
    goBack() {
      const authData = useAuthStore();
      const stationData = useStationStore();
      authData.logout();
      stationData.logout();
      this.$router.push("/login");
    }
  }
};
</script>

<style scoped>
.container {
  width: 100%;
  height: 100%;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
}

.container button {
  width: 60%;
  height: 46px;
  background-color: #1e56a0;
  border: none;
  border-radius: 4px;
  cursor: pointer;
  display: flex;
  justify-content: center;
  align-items: center;
}

.container button h1 {
  font-size: 12px;
  font-family: "Lato", sans-serif;
  font-weight: bold;
  color: white;
}

.button-hovered {
  box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.3);
}

@media (max-width: 800px) {
  .container button {
    width: 50%;
  }
  .container button h1 {
    font-size: 10px;
  }
}

</style>