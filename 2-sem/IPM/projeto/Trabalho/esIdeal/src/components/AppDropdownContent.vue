<template>
    <div v-if="active">
      <slot/>
    </div>
  </template>


  <script>
    export default {
      name: 'AppDropdownContent',
      inject: ['sharedState'],
      props: {
            currentOption: {
            type: String,
            required: true
         }
        },
      computed: {
        active () {
          return this.sharedState.active
        }
      }
    }
    
  </script>