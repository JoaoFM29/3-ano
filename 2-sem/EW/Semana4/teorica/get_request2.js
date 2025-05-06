const axios = require('../../pratica/node_modules/axios');

axios.put('http://localhost:3000/instrumentos/I23', {
    "Nivel": "Amador"
}).then(resp => {
    console.log(resp.data);
}).catch(error => {
    console.log(error);
});
