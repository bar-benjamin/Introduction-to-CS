from sys import argv
import pandas as pd
import re

if len(argv) < 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit()

# read sequence.txt file
with open(argv[2]) as file:
    dna_sequence_txt = file.read()

    # read data.csv file
    df = pd.read_csv(argv[1])
    str_list = df.columns[1:].tolist()

    str_counts_list = []

    # Iterate over the DNA sequences (STRs)
    for str_seq in str_list:
        # Compute the longest run of consecutive repeats of the STR in the DNA sequence to identify
        regex_pattern = '((?:' + str_seq + ')+)'
        max_substring = re.findall(regex_pattern, dna_sequence_txt)
        if max_substring != []:
            # max_substring is a list with 1 element containing the longest run
            max_consecutive_repeats = max(max_substring, key=len).count(str_seq)
            str_counts_list.append(max_consecutive_repeats)

    # checks if the STR counts match exactly with any of the individuals in the CSV file. if there's a match prints his name.
    for index, person in enumerate(df['name'].tolist()):
        if str_counts_list == df.iloc[index, 1:].tolist():
            print(person)
            exit()
    print("no match")
