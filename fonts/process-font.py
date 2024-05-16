import os, shutil, json
from ntpath import dirname
from graph_traversal import createGraph, traverseGraph
from parse_files import processJson, Character, jsonDir, processedDir, prepDirectories, yaffDir, processYaff
from dataclasses import dataclass
from typing import Union



# TODO: flip characters

charScaling = 2
maxSegments = 3

def finalFormatting(charHeight:str, maxWidth:str, charDataArray:str, charArray:str):
    x = \
"""#define CHAR_HEIGHT """ + charHeight  + """
#define MAX_CHAR_WIDTH """ + maxWidth  + """
#define MAX_SEGMENTS """ + str(maxSegments)  + """

typedef struct CharacterData{
    uint8_t first_x;                  // first x value in offset list (allows for less beam oversaturation on prev char)
    uint8_t first_y;                  // first y ''
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



def calculateSegments(font:dict):
    maxWidth = 0
    for c,cData in font.items():
        l = []

        print("Traversing:", c)
        rawSegments = traverseGraph(createGraph(cData.coords))
        segments = []
        for rawSegment in rawSegments:
            s = []
            for index in rawSegment:
                coord = cData.coords[index]
                s.append(charScaling*coord[0])
                s.append(charScaling*coord[1])
            segments.append(s)

        width = charScaling*cData.width
        maxWidth = width if width > maxWidth else maxWidth
        cData.segments = segments
    return maxWidth

def processSegments(font:dict[str,Character]):
    charDataArray = []
    charArray = []

    offset = 0
    # interate over all first page ascii characters
    for i in range(0,128):
        c = chr(i)

        # label creation
        if c in font:
            x = c if c != '\\' else 'backslash'
            label = f" // {x}"
        else:
            label = f""
        if i != 127:
            label = f",{label}"

        # actual processing
        if c in font:
            cData = font[c]
            assert cData.segments is not None
            width = charScaling*cData.width
            length = 0
            lengths = []
            offsets = []
            for i in range(maxSegments):
                l = 0 if i >= len(cData.segments) else len(cData.segments[i])
                length += l
                o = offset
                offset += l
                lengths.append(str(l))
                offsets.append(str(o))
            

            points = [] # flattened segments
            for s in cData.segments:
                points.extend([str(x) for x in s])

            if len(points) > 0:
                charArrayStr = ', '.join(points)
                charArray.append(f"    {charArrayStr}{label} ")
                fx = points[0]
                fy = points[1]
            else:
                fx = 0
                fy = 0 

            charDataArray.append(f"    {{ {fx}, {fy}, {width}, {length}, {len(cData.segments)}, {{{', '.join(offsets)}}}, {{{', '.join(lengths)}}} }}{label}")

        else: # char not in charDict
            charDataArray.append(f"    {{ 0, 0, 0, 0, 0, {{{offset}, {offset}, {offset}}}, {{0, 0, 0}} }}{label}")

    return charDataArray, charArray


def processFiles(dirName):
    dir = os.listdir(dirName)
    for file in dir:
        
        name, extension = file.split(".")
        newFileName = name + ".h"

        with open(f"{dirName}/{file}", "r") as f:
            if extension == "json":
                j = json.load(f)
                font, charHeight = processJson(j)
            elif extension == "yaff":
                font, charHeight = processYaff(f)
            else:
                raise Exception(f"Unknown Extension: {extension}")
            maxWidth = calculateSegments(font)
            charDataArray, charArray = processSegments(font)
            s = finalFormatting(str(charScaling*charHeight), str(maxWidth),"\n".join(charDataArray), "\n".join(charArray))

        with open(f"{processedDir}/{newFileName}", "+w") as f:
            f.write(s)



if __name__ == "__main__":
    prepDirectories()
    processFiles(yaffDir)
