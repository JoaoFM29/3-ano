<template>
  <div id="layout">
    <img id="logo" src="../assets/FullLogo.png"/>
    <form id="form" @submit.prevent="handleSubmit">
      <p>Número de Funcionário</p>
      <input v-model.trim="employeeNumber" placeholder="Número de Funcionário">
      <p>Palavra-passe</p>
      <input v-model.trim="password" placeholder="Palavra-passe" type="password">
      <button :style="buttonStyle" :disabled="isButtonDisabled" type="submit">Login</button>

      <!-- Mostrar a mensagem de erro -->
      <div class="error-container">
        <p class="error-message" v-if="showError">Credenciais inválidas. Tente novamente.</p>
      </div> 
    </form>
  </div>
</template>

<script>
import axios from 'axios';
import { useAuthStore } from '../store/authStore';

const JSON_SERVER_URL = 'http://localhost:3000';

export default {
  name: 'SignInForm',
  data() {
    return {
      mechanicData: {},
      employeeNumber: '',
      password: '',
      showError: false 

    };
  },
  computed: {
    buttonStyle() {
      return {
        backgroundColor: this.isFormFilled ? '#1E56A0' : '#6BABFF',
        cursor: this.isFormFilled ? 'pointer' : 'not-allowed'
      };
    },
    isFormFilled() {
      return this.employeeNumber.trim() !== '' && this.password.trim() !== '';
    },
    isButtonDisabled() {
      return !this.isFormFilled;
    }
  },
  methods: {
    async handleSubmit() {
      try {
        const response = await this.fetchMechanicData();
        if (response === null) {
          this.showError = true;
        }
        else {
          this.mechanicData = response.data;
          if (this.mechanicData.senha === this.password) {
            const authStore = useAuthStore();
            authStore.login(this.mechanicData);
            this.$router.push({ name: 'station' });
          } else {
            this.showError = true;
          }
        }
      } catch (error) {
        console.error('Error fetching data:', error);
      }
    },
    async fetchMechanicData() {
      try {
        return await axios.get(`${JSON_SERVER_URL}/mechanics/${this.employeeNumber}`);
      }catch(error){
        return null
      }

      
    },
  }
};
</script>

<style scoped>
html, body {
  font-family: 'Inter',sans-serif;
  margin: 0;
  padding: 0;
  height: 100%;
}

#layout {
  display: grid;
  height: 100%;
  grid-template-rows: 291px 135px 311px auto 250px;
  grid-template-columns: 31.6% 36.8% 31.6%;
  background-color: var(--background-color);
  gap: 10px;
  grid-template-areas:
    ". . ."
    ". logo ."
    ". form ."
    ". . .";
} 

#logo{
  width: 100%;
  height: 100%;
  grid-area: logo;

}

#form {
  width: 100%;
  height: 100%;
  grid-area: form;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
}

form input {
  font-family: 'Inter',sans-serif;
  display: flex;
  justify-content: center;
  width: 70%;
  height: 48px;
  margin-bottom: 10px;
  border: 1px solid #1E56A0;
  border-radius: 5px;
  margin-left: 7%; /*40px*/
  font-size: 14px;
  text-indent: 10px;
}

form input::placeholder {
  color: #D2D2D2;
}

form p {
  align-self: flex-start;
  margin-left: 18%;
  margin-bottom: 2%;
  font-family: 'Inter',sans-serif;
}

form button {
  width: 25%;
  height: 48px;
  margin-top: 40px;
  margin-left: 20px;
  background-color: #6BABFF;
  color: white;
  border: none;
  border-radius: 4px;
  font-size: 14px;
  cursor: pointer;
}

form button:hover {
  box-shadow: 0px 4px 6px rgba(0, 0, 0, 0.3); /* Add shadow */
}

.error-container {
  display: flex;
  justify-content: center;
  align-items: center;
  padding-top: 20px;
  padding-right: 90px;
  width: 100%;
  height: 5px; /* Altura mínima para a mensagem de erro */
}

.error-message {
  color: red;
  font-size: 14px;
  visibility: visible; /* Certifique-se de que a visibilidade está configurada como visível */
}

@media (max-width: 700px) {
  form input {
    font-size: 12px;
  }
  form button {
    font-size: 12px;
    height: 48px;
    width: 45%;
  }
  form p {
    font-size: 12px;
  }

}
@media (max-width: 500px) {
  #layout {
    display: grid;
    height: 100%;
    grid-template-rows: 291px 135px 251px 291px;
    grid-template-columns: 31.6% 36.8% 31.6%;
    background-color: var(--background-color);
    gap: 10px;
    grid-template-areas:
    ". . ."
    ". logo ."
    ". form ."
    ". . .";
  }

  form input {
    font-size: 8px;
    width: 70%;
    height: 38px;
  }
  form button {
    font-size: 8px;
    height: 38px;
    width: 45%;
    margin-top: 10px;
  }
  form p {
    font-size: 10px;
  }
}
</style>