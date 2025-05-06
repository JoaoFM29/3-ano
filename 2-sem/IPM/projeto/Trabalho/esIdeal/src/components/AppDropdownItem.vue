<template>
    <div class ="dropdown-item" v-if="text !== currentOption" @click="selectItem">
        <div class ="item">
            <!-- <slot></slot> -->
            {{ text }}
        </div>
    </div>
  </template>

  <script>
export default {
  name: 'AppDropdownItem',
  props: {
    currentOption: {
      type: String,
      required: true
    },
    text: {
      type: String,
      required: true
    }
  },
  methods: {
    selectItem() {
      this.$emit('item-selected', this.text);
    }
  }
}
</script>

<style scoped>
.dropdown-item {
  cursor: pointer;
  transition: background-color 0.3s ease;

  display: flex;
  align-items: center;
  justify-content: center;
  width: 318px;
  height: 44px;
  background-color: #fff;
  border-style: solid;
  border-width: 1px;
  border-color: #000;
}
.dropdown-item .item{

  display: flex;
  align-items: center;
  justify-content: space-between;
  width: 90%;
  font-size: 16px;
  font-family: 'Inter', sans-serif;

}

.dropdown-item:hover {
  background-color: #f5f5f5;
}

@media (max-width: 1350px) {
  .dropdown-item {
    width: 238px;
  }
}

@media (max-width: 1024px) {
  .dropdown-item {
    width: 180px;
  }
}

@media (max-width: 800px) {
  .dropdown-item {
    width: 150px;
  }
  .dropdown-item .item{
    font-size: 12px;
  }
}
</style>
