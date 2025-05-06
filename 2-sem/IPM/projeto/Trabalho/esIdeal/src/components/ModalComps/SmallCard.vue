<template>
    <p>{{service.descr}}</p>
</template>

<script>

export default {
    name: 'SmallCard',
    props: {
    service: {
      type: Object,
      required: true,
    },
    }
} 
    
</script>


<style scope>

</style>