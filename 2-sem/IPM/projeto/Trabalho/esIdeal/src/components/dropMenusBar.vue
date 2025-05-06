<template>
  <div class="menus-container">
    <div class="ord-wrapper" id="ordenacao">
      <h1>Ordenação:</h1>
      <AppDropdown>
        <template v-slot:button>
          <div>{{ buttonText1 }}</div>
        </template>
        <template v-slot:dropdown>
          <AppDropdownContent :currentOption="buttonText1" class="down-wrapper">
            <AppDropdownItem @item-selected="updateButtonText1" :currentOption="buttonText1" text="Data de Chegada"></AppDropdownItem>
            <AppDropdownItem @item-selected="updateButtonText1" :currentOption="buttonText1" text="Menor duração Média"></AppDropdownItem>
            <AppDropdownItem @item-selected="updateButtonText1" :currentOption="buttonText1" text="Maior duração Média"></AppDropdownItem>
            <AppDropdownItem @item-selected="updateButtonText1" :currentOption="buttonText1" text="Data de Conclusão"></AppDropdownItem>
          </AppDropdownContent>
        </template>
      </AppDropdown>
    </div>
    <div class="ord-wrapper" id="estado">
      <h1>Estado:</h1>
      <AppDropdown>
        <template v-slot:button>
          <div>{{ buttonText2 }}</div>
        </template>
        <template v-slot:dropdown>
          <AppDropdownContent :currentOption="buttonText2" class="down-wrapper">
            <AppDropdownItem @item-selected="updateButtonText2" :currentOption="buttonText2" text="Por Realizar"></AppDropdownItem>
            <AppDropdownItem @item-selected="updateButtonText2" :currentOption="buttonText2" text="A Decorrer"></AppDropdownItem>
            <AppDropdownItem @item-selected="updateButtonText2" :currentOption="buttonText2" text="Suspenso"></AppDropdownItem>
            <AppDropdownItem @item-selected="updateButtonText2" :currentOption="buttonText2" text="Realizado"></AppDropdownItem>
            <AppDropdownItem @item-selected="updateButtonText2" :currentOption="buttonText2" text="Todos"></AppDropdownItem>
          </AppDropdownContent>
        </template>
      </AppDropdown>
    </div>
    <div class="ord-wrapper" id="agendamento">
      <h1>Agendamento:</h1>
      <AppDropdown>
        <template v-slot:button>
          <div>{{ buttonText3 }}</div>
        </template>
        <template v-slot:dropdown>
          <AppDropdownContent :currentOption="buttonText3" class="down-wrapper">
            <AppDropdownItem @item-selected="updateButtonText3" :currentOption="buttonText3" text="Todos"></AppDropdownItem>
            <AppDropdownItem @item-selected="updateButtonText3" :currentOption="buttonText3" text="Fila de Espera"></AppDropdownItem>
            <AppDropdownItem @item-selected="updateButtonText3" :currentOption="buttonText3" text="Programados"></AppDropdownItem>
          </AppDropdownContent>
        </template>
      </AppDropdown>
    </div>
  </div>
</template>

<script>
import AppDropdown from '../components/AppDropdown.vue'
import AppDropdownContent from '../components/AppDropdownContent.vue'
import AppDropdownItem from '../components/AppDropdownItem.vue'

export default {
  name: 'DropMenuBar',
  components: {
    AppDropdown,
    AppDropdownContent,
    AppDropdownItem,
  },
  data() {
    return {
      buttonText1: 'Data de Chegada',
      buttonText2: 'Por Realizar',
      buttonText3: 'Todos'
    }
  },
  methods: {
    updateButtonText1(text) {
      this.buttonText1 = text;
      this.$emit('orderChanged', [this.buttonText1,this.buttonText2,this.buttonText3])
    },
    updateButtonText2(text) {
      this.buttonText2 = text;
      this.$emit('orderChanged', [this.buttonText1,this.buttonText2,this.buttonText3])
    },
    updateButtonText3(text) {
      this.buttonText3 = text;
      this.$emit('orderChanged', [this.buttonText1,this.buttonText2,this.buttonText3])
    }
  }
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

@media (max-width: 1024px){
  .ord-wrapper h1 {
    font-size: 14px;
  }
}

@media (max-width: 800px){
  .ord-wrapper h1 {
    font-size: 12px;
  }
}

</style>