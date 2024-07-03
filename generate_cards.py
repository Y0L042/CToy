import csv
import json

# Define the default card configuration
default_card = {
    "default_bgcolor": { "r": 0, "g": 121, "b": 241, "a": 255 },
    "def_whratio": 0.66,
    "def_height": 200,
    "def_width": 0.66 * 200,  # Calculated from defHeight * defWHRatio
    "num_size": 15,
    "num_y_spacing": 30,
    "num_x_spacing": 20,
    "num_pos": { "x": 25, "y": 25 },
    "num_color": { "r": 0, "g": 255, "b": 0, "a": 255 },  # GREEN in RGBA
    "name_size": 15,
    "name_pos": { "x": 10, "y": 30 },
    "name_color": { "r": 0, "g": 255, "b": 0, "a": 255 }  # GREEN in RGBA
}

# Read the CSV file and generate the card list
cards = []

csv_file = './data/skyrim_triple_triad_cards.csv'
with open(csv_file, mode='r') as file:
    csv_reader = csv.DictReader(file)
    for row in csv_reader:
        card = {
            "nums": [
                int(row["Top"]),
                int(row["Right"]),
                int(row["Bottom"]),
                int(row["Left"])
            ],
            "name": row["Name"],
            "img_path": ""  # Placeholder for image path, can be customized
        }
        cards.append(card)

# Create the final JSON structure
output_json = {
    "default_card": default_card,
    "cards": cards
}

# Write the JSON structure to a file
json_file = './data/cards.json'
with open(json_file, mode='w') as file:
    json.dump(output_json, file, indent=4)

print(f"JSON data has been written to {json_file}")
