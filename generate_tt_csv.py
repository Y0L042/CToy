import csv
import random

# List of 53 Skyrim names (for demonstration purposes, you can add actual names)
skyrim_names = [
    "Aela the Huntress", "Alduin", "Astrid", "Balgruuf the Greater", "Brynjolf", 
    "Cicero", "Delphine", "Dragonborn", "Esbern", "Farengar Secret-Fire", 
    "Farkas", "Gormlaith Golden-Hilt", "Harkon", "Jarl Elisif the Fair", 
    "Karliah", "Kodlak Whitemane", "Lydia", "Maven Black-Briar", "Mercer Frey", 
    "Miraak", "Nazeem", "Paarthurnax", "Ralof", "Serana", "Sinding", "Sofia", 
    "Sovngarde Hero", "Stormcloak Soldier", "Thalmor Justiciar", "Ulfric Stormcloak", 
    "Urag gro-Shub", "Vex", "Vilkas", "Ysgramor", "Alduin's Wall", "Auriel's Bow", 
    "Azura's Star", "Black-Briar Mead", "Blades Armor", "Daedric Artifact", 
    "Dawnbreaker", "Dragon Priest Mask", "Ebony Blade", "Ebony Warrior", 
    "Elder Scroll", "Falmer", "Glass Sword", "Hircine's Ring", "Iron Helmet", 
    "Mehrunes' Razor", "Nightingale Armor", "Spellbreaker", "Wabbajack"
]

# Function to generate random card values
def generate_card_values():
    return [random.randint(1, 10) for _ in range(4)]

# Create the CSV file
with open('assets/skyrim_triple_triad_cards.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    # Write the header
    writer.writerow(["Top", "Right", "Bottom", "Left", "Name"])
    # Write the card data
    for name in skyrim_names:
        values = generate_card_values()
        writer.writerow(values + [name])

print("CSV file 'assets/skyrim_triple_triad_cards.csv' created successfully!")
