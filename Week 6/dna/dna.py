import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read database file into a variable
    dna = []
    db_filename = sys.argv[1]
    with open(db_filename) as file_db:
        reader = csv.DictReader(file_db)
        for name in reader:
            for key in name:
                if key in ['AGATC', 'AATG', 'TATC', 'TTTTTTCT', 'TCTAG', 'GATA', 'GAAA', 'TCTG']:
                    name[key] = int(name[key])
            dna.append(name)

    # Read DNA sequence file into a variable
    sq_filename = sys.argv[2]
    with open(sq_filename) as file_sq:
        dna_sequence = file_sq.read()

    # Find longest match of each STR in DNA sequence
    sequence_counter = {}
    subsequences = ['AGATC', 'AATG', 'TATC', 'TTTTTTCT', 'TCTAG', 'GATA', 'GAAA', 'TCTG']
    for subsequence in subsequences:
        if subsequence in dna_sequence:
            sequence_counter[subsequence] = longest_match(dna_sequence, subsequence)

    # Check database for matching profiles
    # set "match goal" for conditional statements in for loop based on database loaded
    if sys.argv[1] == 'databases/small.csv':
        match_goal = 2
    elif sys.argv[1] == 'databases/large.csv':
        match_goal = 7

    # for every name dictionary in the list of DNA dictionaries
    for name in dna:
        # track matches
        match_counter = 0
        # for every STR check possible
        for subsequence in subsequences:
            # if match is found and is all and last matches print name
            if sequence_counter.get(subsequence) == name[subsequence] and match_counter == match_goal:
                print(name["name"])
                return
            # if match is found but not last match possible match, add to match counter
            elif sequence_counter.get(subsequence) == name[subsequence]:
                match_counter += 1
            else:
                break

    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
