import os
import re
import string

filepath = os.path.join(os.path.dirname(__file__), 'CS210_Project_Three_Input_File.txt')
freqpath = os.path.join(os.path.dirname(__file__), 'frequency.dat')

def GetItemsFromFile():
    lines = []
    items = {}

    with open(filepath) as f:
        lines = [ line.strip() for line in f ]

    for line in lines:
        if not line in items:
            items[line] = 0
        items[line] += 1

    return items

def PrintItemsPurchasedFrequency():
    items = GetItemsFromFile()

    for item, count in items.items():
        print(f"{item}: {count}")

def PrintItemPurchaseFrequency(item_name):
    print(f"\nLocating today's purchase frequency for: {item_name}...")

    items = GetItemsFromFile()
    
    if item_name in items.keys():
        return items[item_name]
    else:
        return 0

def GeneratePurchaseFrequencyReport():
    items = GetItemsFromFile()

    with open(freqpath, "w") as file:
        for item, count in items.items():
            file.write(f"{item} {count}\n")