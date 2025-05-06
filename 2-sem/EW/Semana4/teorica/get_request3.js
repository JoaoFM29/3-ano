const axios = require('../pratica/node_modules/axios');

axios.delete('http://localhost:3000/alunos/A4140')
.then(resp => {
    console.log(resp.data);
}).catch(error => {
    console.log(error);
});
