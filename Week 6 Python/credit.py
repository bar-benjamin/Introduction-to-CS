from cs50 import get_int


def countDigits(number):
    return len(str(abs(number)))
    

def getFirstDigit(number):
    return int(str(number)[:1])


def getFirst2Digits(number):
    return int(str(number)[:2])


def calculate_checksum(card_number):
    num_of_digits = countDigits(card_number)
    sum = 0
    
    for i in range(num_of_digits):
        last_digit = card_number % 10

        digits_product = last_digit * ((i % 2) + 1)
        sum += digits_product if digits_product <= 9 else digits_product - 9
        
        card_number //= 10
        
    return sum


def printCardType(num_of_digits, first_two_digits):
    if num_of_digits == 15 and str(first_two_digits) in ['34', '37']:
        print("AMEX")
    elif num_of_digits == 16 and 51 <= first_two_digits <= 55:
        print("MASTERCARD")
    elif str(num_of_digits) in ['13', '16'] and (first_two_digits // 10) == 4:
        print("VISA")
    else:
        print("INVALID")


card_number = get_int("Number: ")
checksum = calculate_checksum(card_number)
if checksum % 10 == 0:
    printCardType(countDigits(card_number), getFirst2Digits(card_number))
else:
    print("INVALID")