document.addEventListener('DOMContentLoaded', () => {
    const urlParams = new URLSearchParams(window.location.search);
    const personId = urlParams.get('id');

    //A string vazia é como se fosse false em js
    //Quando se quer editar uma entrada
    if (personId) {
        // Carregar dados da pessoa
        axios.get(`/api/pessoas/${personId}`)
            .then(response => {
                const person = response.data;
                fillEditForm(person); // Preencher o formulário
            })
            .catch(error => {
                console.error('Erro ao carregar pessoa para edição:', error);
            });
    }

    //Quando se quer adicionar uma nova entrada
    else {
        const editPersonForm = document.getElementById('edit-person-form');
        editPersonForm.addEventListener('submit', event => {
            event.preventDefault();
    
            const formData = new FormData(editPersonForm);
            const updatedPerson = {
                nome: formData.get('name'),
                idade: parseInt(formData.get('age')),
                sexo: formData.get('sex'),
                morada: {
                    cidade: formData.get('city'),
                    distrito: formData.get('district')
                },
                BI: formData.get('bi'),
                descrição: formData.get('description'),
                profissao: formData.get('occupation'),
                partido_politico: {
                    party_abbr: formData.get('partyAbbr'),
                    party_name: formData.get('partyName')
                },
                religiao: formData.get('religion'),
                desportos: formData.getAll('sports'),
                animais: formData.getAll('animals'),
                figura_publica_pt: formData.getAll('publicFigures'),
                marca_carro: formData.get('carBrand'),
                destinos_favoritos: formData.getAll('favoriteDestinations'),
                atributos: {
                    fumador: formData.has('smoker'),
                    gosta_cinema: formData.has('likesMovies'),
                    gosta_viajar: formData.has('likesTraveling'),
                    acorda_cedo: formData.has('earlyRiser'),
                    gosta_ler: formData.has('likesReading'),
                    gosta_musica: formData.has('likesMusic'),
                    gosta_comer: formData.has('likesEating'),
                    gosta_animais_estimacao: formData.has('likesPets'),
                    gosta_dancar: formData.has('likesDancing'),
                    comida_favorita: formData.get('favoriteFood')
                }
            };
    
            axios.put(`/api/pessoas/${personId}`, updatedPerson)
            .then(response => {
                console.log('Resposta do servidor após atualização:', response.data);
                // Redirecionar após a atualização bem-sucedida
                window.location.href = 'http://localhost:3000/';
            })
            .catch(error => {
                console.error('Erro ao atualizar pessoa:', error);
                if (error.response) {
                    console.error('Resposta de erro do servidor:', error.response.data);
                }
            });
        });
    }

    function fillEditForm(person) {
        const formFields = {
            'name': 'nome',
            'age': 'idade',
            'sex': 'sexo',
            'city': 'morada.cidade',
            'district': 'morada.distrito',
            'bi': 'BI',
            'description': 'descrição',
            'occupation': 'profissao',
            'partyAbbr': 'partido_politico.party_abbr',
            'partyName': 'partido_politico.party_name',
            'religion': 'religiao',
            'sports': 'desportos',
            'animals': 'animais',
            'publicFigures': 'figura_publica_pt',
            'carBrand': 'marca_carro',
            'favoriteDestinations': 'destinos_favoritos',
            'smoker': 'atributos.fumador',
            'likesMovies': 'atributos.gosta_cinema',
            'likesTraveling': 'atributos.gosta_viajar',
            'earlyRiser': 'atributos.acorda_cedo',
            'likesReading': 'atributos.gosta_ler',
            'likesMusic': 'atributos.gosta_musica',
            'likesEating': 'atributos.gosta_comer',
            'likesPets': 'atributos.gosta_animais_estimacao',
            'likesDancing': 'atributos.gosta_dancar',
            'favoriteFood': 'atributos.comida_favorita'
        };

        Object.keys(formFields).forEach(field => {
            const fieldValue = getFieldFromPath(person, formFields[field]);
            const inputElement = document.getElementById(field);

            if (inputElement) {
                inputElement.value = fieldValue
            }
        });
    }

    function getFieldFromPath(obj, path) {
        const properties = path.split('.');
        let value = obj;

        for (const property of properties) {
            value = value ? value[property] : undefined;
        }

        return value;
    }
    
    const backButton = document.getElementById('backButton');

    if (backButton) {
        backButton.addEventListener('click', event => {
            event.preventDefault();
            const editUrl = `http://localhost:3000/`;
            window.location.href = editUrl;
        });
    }
    
});
