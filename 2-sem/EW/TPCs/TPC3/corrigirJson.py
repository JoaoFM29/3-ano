import json

def convert_to_json_array(input_file, output_file):
    # Read individual JSON objects from the input file
    with open(input_file, 'r') as file:
        json_objects = [json.loads(line) for line in file]

    # Write the combined JSON array to the output file
    with open(output_file, 'w') as file:
        json.dump(json_objects, file, indent=2)

if __name__ == "__main__":
    input_filename = "filmes.json"  # Replace with your input file name
    output_filename = "filmesDireitos.json"  # Replace with your desired output file name

    convert_to_json_array(input_filename, output_filename)
