from cs50 import get_int


def main():
    height = get_height()
    # for each row
    for i in range(height):
        # for each column print spaces and bricks
        print(" " * (height - (i + 1)), end='')
        print("#" * (i + 1), end="  ")
        print("#" * (i + 1))


def get_height():
    while True:
        n = get_int("Height: ")
        # make sure Height is a positive value
        if 9 > n > 0:
            return n


main()