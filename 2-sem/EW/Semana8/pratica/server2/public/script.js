document.addEventListener('DOMContentLoaded', () => {
    const loadPeopleList = () => {
        axios.get('/api/pessoas')
            .then(response => {
                const people = response.data;
                const peopleListElement = document.getElementById('people-list');
                peopleListElement.innerHTML = '';

                people.forEach(person => {
                    const listItem = document.createElement('li');
                    listItem.textContent = `${person.nome}`;

                    //botão de remover entrada 
                    const deleteButton = document.createElement('button');
                    deleteButton.textContent = 'Delete';
                    deleteButton.addEventListener('click', () => {
                        axios.delete(`/api/pessoas/${person._id}`)
                            .then(() => {
                                listItem.remove();
                            })
                            .catch(error => {
                                console.error('Erro ao deletar pessoa:', error);
                            });
                    });

                    //botão de editar entrada 
                    const editButton = document.createElement('button');
                    editButton.textContent = 'Edit';
                    editButton.addEventListener('click', () => {
                        redirectToEditPage(person._id); // redireciona para a pagina de edição
                    });

                    listItem.appendChild(deleteButton);
                    listItem.appendChild(editButton);
                    peopleListElement.appendChild(listItem);
                });
            })
            .catch(error => {
                console.error('Erro ao carregar lista de pessoas:', error);
            });
    };

    const redirectToEditPage = (personId) => {
        const editUrl = `/edit.html?id=${personId}`;
        window.location.href = editUrl;
    };

    loadPeopleList();
});
