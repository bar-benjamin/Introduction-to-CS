from cs50 import get_int

height = get_int("Height: ")
while height > 8 or height < 1:
    height = get_int("Height: ")

# using Python "string multiplication" property
for row in range(1, height + 1):
    spaces_num = height - row
    hashes_num = row
    # prints each row's hashes
    print(" " * spaces_num + "#" * hashes_num + "  " + "#" * hashes_num)