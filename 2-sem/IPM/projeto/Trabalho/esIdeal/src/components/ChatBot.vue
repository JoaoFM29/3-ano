<template>
    <p></p>
</template>

<script>
export default {
    name: "ChatBotComponent",
    methods: {
    },
    mounted (){
      (function(d, m){
        var kommunicateSettings = {"appId":"184b8d6051d8e64fa4a554b3c50c1ff38","popupWidget":true,"automaticChatOpenOnNavigation":true};
        var s = document.createElement("script"); s.type = "text/javascript"; s.async = true;
        s.src = "https://widget.kommunicate.io/v2/kommunicate.app";
        var h = document.getElementsByTagName("head")[0]; h.appendChild(s);
        window.kommunicate = m; m._globals = kommunicateSettings;
      })(document, window.kommunicate || {});
    },
    data: function(){
    }
}
</script>