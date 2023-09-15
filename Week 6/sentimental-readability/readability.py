
def main():
    # get string from user
    text = input("Text: ")
    letter_counter, word_counter, sentence_counter = string_counts(text)
    # define grading index
    index = round((0.0588 * ((letter_counter * 100) / word_counter)) - (0.296 * ((sentence_counter * 100) / word_counter)) - 15.8)

    # print grade based on index
    if 0 < index <= 16:
        print(f"Grade {index}")
    elif index < 1:
        print("Before Grade 1")
    else:
        print("Grade 16+")
    return 0


def string_counts(a):
    letter_counter = 0
    word_counter = 0
    sentence_counter = 0
    # loop through phrases counting letters words and sentences
    for i in range(len(a)):
        # Count letter if alpha
        if a[i].isalpha():
            letter_counter += 1
        # assess if end of string
        elif i == len(a) - 1:
            # if ends with quotation only count word
            if a[i] == '"':
                word_counter += 1
            # else must be end of word and sentence
            else:
                word_counter += 1
                sentence_counter += 1
        # count spaces as words
        elif a[i].isspace():
            word_counter += 1
        # count punctuation as sentences
        elif a[i] == '.' or a[i] == '!' or a[i] == '?':
            sentence_counter += 1
    return letter_counter, word_counter, sentence_counter


if __name__ == "__main__":
    main()