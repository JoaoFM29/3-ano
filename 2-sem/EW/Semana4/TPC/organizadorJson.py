import json

def transform_dataset(input_file):
    with open(input_file, 'r') as file:
        data = json.load(file)

    filmes = []
    atores = set()
    generos = set()
    ocorrAtor = 1

    for filme_data in data:
        # Process Cast
        cast = filme_data.get("cast", [])
        for actor in cast:
            ator_entry = {
                "id": ocorrAtor,
                "ator": actor
            }
            ocorrAtor += 1
            atores.add(tuple(ator_entry.items()))

        # Process Genres
        genres = filme_data.get("genres", [])
        generos.update(genres)

        # Create Movie Entry
        movie_entry = {
            "_id": filme_data["_id"]["$oid"],
            "title": filme_data["title"],
            "year": filme_data["year"],
            "cast": cast,
            "genres": genres
        }

        filmes.append(movie_entry)

    result = {
        "Filmes": filmes,
        "Atores": [dict(ator) for ator in atores],
        "Generos": list(generos)
    }

    with open("filmesPronto.json", 'w') as output_file:
        json.dump(result, output_file, indent=2)

if __name__ == "__main__":
    transform_dataset("filmesDireitos.json")