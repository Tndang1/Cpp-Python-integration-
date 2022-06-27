from asyncio.windows_events import NULL
import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100

def SquareValue(v):
    return v * v

def countAll():
    with open("inputfile.txt", "r") as file:
        itemlist = file.read().split()
    counts = dict()
    for i in itemlist:
        if i in counts:
            counts[i] += 1
        else:
            counts[i] = 1
    return counts

def printAll():
    counts = countAll()
    for item, count in sorted(counts.items()):
        print (item, count)
    print()

def countSpecific(item):
    counts = countAll()
    if item in counts:
        return counts[item]
    else:
        return 0

def writeFreqFile():
    counts = countAll()
    with open("frequency.dat", "w+") as file:
        for item, count in sorted(counts.items()):
            file.write('%s %s \n' % (item, count))