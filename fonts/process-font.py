import os, shutil, json
from ntpath import dirname
from graph_traversal import createGraph, traverseGraph


# TODO: flip characters

charScaling = 3
maxSegments = 3

def finalFormatting(charHeight:str, charDataArray:str, charArray:str):
    x = \
"""#define CHAR_HEIGHT """ + charHeight  + """
#define MAX_SEGMENTS """ + str(maxSegments)  + """

typedef struct CharacterData{
    uint8_t width;                  // full width of the character
    uint8_t length;                 // number of bytes for full char
    uint8_t segments;               // number of segments
    uint16_t offsets[MAX_SEGMENTS]; // offsets into characterArray for the start of each segment
    uint16_t lengths[MAX_SEGMENTS]; // number of bytes for segment
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

def getCharDict(j:dict):
    charDict = {}
    for glyph in j["glyphs"]:
        l = []

        print("Traversing:", glyph['name'])
        rawSegments = traverseGraph(createGraph(glyph['coords']))
        segments = []
        for rawSegment in rawSegments:
            s = []
            for index in rawSegment:
                coord = glyph["coords"][index]
                s.append(charScaling*coord[0])
                s.append(charScaling*coord[1])
            segments.append(s)

        charDict[glyph['name']] = {
            "width":charScaling*glyph["width"], 
            "segments": segments
        }
    return charDict

def processChars(charDict:dict):
    charDataArray = []
    charArray = []

    offset = 0
    # interate over all first page ascii characters
    for i in range(0,128):
        c = chr(i)

        # label creation
        if c in charDict:
            x = c if c != '\\' else 'backslash'
            label = f" // {x}"
        else:
            label = f""
        if i != 127:
            label = f",{label}"

        # actual processing
        if c in charDict:
            cd = charDict[c]
            width = cd["width"]
            length = 0
            lengths = []
            offsets = []
            for i in range(maxSegments):
                l = 0 if i >= len(cd["segments"]) else len(cd["segments"][i])
                length += l
                o = offset
                offset += l
                lengths.append(str(l))
                offsets.append(str(o))

            
            charDataArray.append(f"    {{ {width}, {length}, {len(cd['segments'])}, {{{', '.join(offsets)}}}, {{{', '.join(lengths)}}} }}{label}")

            points = [] # flattened segments
            for s in cd["segments"]:
                points.extend([str(x) for x in s])
            if len(points) > 0:
                charArrayStr = ', '.join(points)
                charArray.append(f"    {charArrayStr}{label} ")

        else: # char not in charDict
            charDataArray.append(f"    {{ 0, 0, 0, {{{offset}, {offset}, {offset}}}, {{0, 0, 0}} }}{label}")

    return charDataArray, charArray

def resetList(l):
    for i in range(len(l)):
        l[i] = 0

def processFile(j:dict):
    charHeight = str(charScaling*j["height"])
    charDict = getCharDict(j)
    charDataArray, charArray = processChars(charDict)
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
