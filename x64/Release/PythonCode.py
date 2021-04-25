import re
import string
import os



# Helper function - Checks for valid file path, reads file, and returns file contents
def ReadFile():
    try:
        # find file path
        filepath = os.getcwd() + "\CS210_Project_Three_Input_File.txt" # FIXME: refactor to enable runtime file selection
        # try to open the file
        with open(filepath) as f:
            # read file contents
            file_content = f.read().splitlines()
        # return file contents
        return file_content
    # catching exceptions
    except: # TODO: explicitly handle specific exceptions raised by try block
        print('Error! File not found!')

# Helper function - counts frequency of elements in file contents and returns dict with results
def CountItems(file_contents):
    # create new dict for storing results of parsing
    item_counts = {}
    # loop through file contents
    for item in file_contents:
        # if item is already in the results dict, increment key
        if item in item_counts:
            item_counts[item] += 1
        # else add item to results dict
        else:
            item_counts[item] = 1
    return item_counts

# Prints a list of file contents and how many times each one appears in the list
def ItemCount():
    # cache file contents
    item_list = ReadFile()
    # create new dict for storing results of parsing
    item_counts = CountItems(item_list)
    # holds max length of item names for formatting the output later
    max_len = 0
    # loop through item_counts to find max item name length
    for item in item_counts:
        # if item name length is new max, save new max
        max_len = len(item) if len(item) > max_len else max_len
    # print results dict with formatting for easier reading
    for key, value in item_counts.items():
        print(f'{key:.<{max_len}}{value:.>16}')

# Reads file and returns frequency of user specified item
def ItemFreq(item_name):
    # cache file contents
    item_list = ReadFile()
    # create new dict for storing results of parsing
    item_counts = CountItems(item_list)
    # if the item name exists in the file, return its count
    if item_name in item_counts:
        return item_counts[item_name]
    # if item wasn't on the list, return 0
    else:
        return 0

# Reads file and writes frequency.dat formatted for histogram printing back in C++
def WriteFreqFile():
    # cache file contents
    item_list = ReadFile()
    # create new dict for storing results of parsing
    item_counts = CountItems(item_list)
    # cache file name
    filename = "frequency.dat" # TODO: refactor to enable runtime file name selection
    try:
        # open file and overwrite contents if already exists
        with open(filename, "w") as f:
            # write values to file
            f.writelines(f'{key} {val}\n' for key, val in item_counts.items())
    except: # TODO: explicitly handle specific exceptions raised by try block
        print('Error! File could not be created and/or written!')