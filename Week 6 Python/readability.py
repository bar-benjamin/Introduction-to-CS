from cs50 import get_string
import re

text = get_string("Text: ")

letters = len(re.findall("[a-zA-Z]", text))
sentences = len(re.findall("[!\.\?]", text))
# if there are no spaces we have exactly 1 word if we find 1 space we have two words etc
words = text.count(' ') + 1


index = 0.0588 * (100 * letters / words) - 0.296 * (100 * sentences / words) - 15.8

if 1 <= index < 16:
    print("Grade {}".format(round(index)))
elif index >= 16:
    print("Grade 16+")
else:
    print("Before Grade 1")