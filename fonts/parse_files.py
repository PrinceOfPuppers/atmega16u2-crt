import os, shutil
from io import TextIOWrapper
from ntpath import dirname

from dataclasses import dataclass
from typing import Union

@dataclass
class Character:
    c:int
    width:int
    coords:list[list[int]]
    segments:Union[list[list[int]], None] = None

scriptDir = dirname(__file__)
jsonDir = f"{scriptDir}/json"
yaffDir = f"{scriptDir}/yaff"
processedDir = f"{scriptDir}/processed"

def prepDirectories():
    if not os.path.exists(jsonDir) or len(os.listdir(jsonDir)) == 0:
        raise Exception(f"No Raw Data To Process in {processedDir}")

    if os.path.exists(processedDir):
        shutil.rmtree(processedDir)
    os.mkdir(processedDir)


def processJson(j:dict):
    font = {}
    height = j['height']
    for glyph in j["glyphs"]:
        c = Character(ord(glyph["name"]), glyph["width"], glyph["coords"])
        font[glyph["name"]] = c
    return font, height

def processYaff(f:TextIOWrapper):
    font = {}
    height = 0
    while True:
        line = f.readline()
        if not line:
            break
        if line[0:2] != "u+":
            continue
        unicodeNumber = int(line.strip().strip(":")[2:],16)
        c = chr(unicodeNumber)

        # we only care about ascii
        if unicodeNumber > 255:
            continue

        # ignore duplicates
        if c in font:
            continue

        while line[0] != " ":
            line = f.readline()

        # here we process the ascii character
        coords = []
        y = 0
        width = 0
        while True:
            line = line.strip()
            if len(line) == 0:
                break
            width = len(line)
            for x, char in enumerate(line):
                if char == '.':
                    continue
                coords.append([x, y])
            y+=1
            line = f.readline()
        height = y + 1
        
        font[c] = Character(unicodeNumber, width, coords)

    return font, height

if __name__ == "__main__":
    with open(f"{scriptDir}/yaff/pet.yaff", "r") as f:
        font, height = processYaff(f)
        for c, data in font.items():
            print(c, data.width)

