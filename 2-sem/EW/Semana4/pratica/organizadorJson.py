import json

def transform_dataset(input_file):
    with open(input_file, 'r') as file:
        data = json.load(file)

    animals = {}
    animal_id_counter = 1
    occurrences = []
    species = {}

    for occurrence in data.get("Ocorrencias", []):
        # Process Animals
        species_id_desc = occurrence.get("SpeciesIDDesc", "")
        if species_id_desc and species_id_desc not in animals:
            animals[species_id_desc] = {"id": animal_id_counter, "designation": species_id_desc}
            animal_id_counter += 1

        # Process Species
        animal_id = animals.get(species_id_desc, {}).get("id", None)
        if animal_id is not None and species_id_desc not in species:
            species[species_id_desc] = {"id": animal_id, "designation": species_id_desc, "AnimalID": animal_id}

        # Add reference to AnimalID in Occurrences
        occurrence["AnimalID"] = animal_id
        occurrences.append(occurrence)

    result = {
        "Ocorrencias": occurrences,
        "Especies": list(species.values()),
        "Animais": list(animals.values())
    }

    with open("mordidasAnimaisOrganizado.json", 'w') as output_file:
        json.dump(result, output_file, indent=2)

if __name__ == "__main__":
    transform_dataset("mordidasAnimais.json")
