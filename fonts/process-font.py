import os, shutil, json
from ntpath import dirname


# TODO: flip characters

charScaling = 3

def finalFormatting(charHeight:str, charDataArray:str, charArray:str):
    x = \
"""#define CHAR_HEIGHT""" + charHeight  + """

typedef struct CharacterData{
    uint8_t width;
    uint16_t offset;
    uint16_t length;
} CharacterData;

const CharacterData characterDataArray[] PROGMEM = {
""" + \
charDataArray +\
"""
};

const uint8_t characterArray[] PROGMEM = {
""" + \
charArray +\
"""
};"""
    return x


scriptDir = dirname(__file__)
rawDir = f"{scriptDir}/raw"
processedDir = f"{scriptDir}/processed"

def prepDirectories():
    if not os.path.exists(rawDir) or len(os.listdir(rawDir)) == 0:
        raise Exception(f"No Raw Data To Process in {processedDir}")

    if os.path.exists(processedDir):
        shutil.rmtree(processedDir)
    os.mkdir(processedDir)

def processFile(j:dict):
    charHeight = str(charScaling*j["height"])
    charDict = {}
    for g in j["glyphs"]:

        l = []
        for coord in g["coords"]:
            l.append(str(charScaling*coord[0]))
            l.append(str(charScaling*coord[1]))

        charDict[g["name"]] = {
            "width":g["width"], 
            "coords": l
        }

    # interate over all first page ascii characters
    charDataArray = []
    charArray = []
    offset = 0
    for i in range(0,128):
        c = chr(i)
        length = 0
        width = 0
        label = ""
        charArrayStr = ""
        if c in charDict:
            length = len(charDict[c]["coords"])
            width = charScaling*charDict[c]["width"]
            #charArray.extend(charDict[c]["coords"])
            charArrayStr = ', '.join(charDict[c]['coords'])
            x = c if c != '\\' else 'backslash'
            label = f" // {x}"

        if i != 127:
            label = f",{label}"

        charDataArray.append(f"    {{ {width}, {offset}, {length} }}{label}")
        if charArrayStr:
            charArray.append(f"    {charArrayStr}{label} ")
        offset += length

    return finalFormatting(charHeight ,"\n".join(charDataArray), "\n".join(charArray))


def processFiles():
    dir = os.listdir(rawDir)
    for file in dir:
        with open(f"{rawDir}/{file}", "r") as f:
            j = json.load(f)
            s = processFile(j)

        newFileName = file.split(".")[0] + ".h"
        with open(f"{processedDir}/{newFileName}", "+w") as f:
            f.write(s)



if __name__ == "__main__":
    prepDirectories()
    processFiles()
