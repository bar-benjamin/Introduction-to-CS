#include <stdio.h>
#include <cs50.h>
#include <math.h>

int countDigits(long num)
{
    return (num == 0) ? 1 : (log10(num) + 1);
}

int getFirstDigit(long num)
{
    return (int)(num / pow(10, countDigits(num) - 1)); 
}

int getFirst2Digits(long num)
{
    while (num >= 100) 
    {
        num /= 10;
    }
    return num;
}

/**
 * Luhn's Algorithm: determine if a credit card number is (syntactically) valid
 * 1. Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products' digits together.
 * 2. Add the sum to the sum of the digits that weren't multiplied by 2.
 * 3. If the total's last digit is 0 then the number is valid!
 */ 
int calculate_checksum(long num)
{
    int sum = 0, last_digit = 0, digits_product = 0;
    int num_of_digits = countDigits(num);

    for (int i = 0; i < num_of_digits; ++i)
    {
        last_digit = num % 10;

        digits_product = last_digit * ((i % 2) + 1); // multiply number by its weight - 1 or 2
        sum += (digits_product > 9) ? digits_product - 9 : digits_product; // if the digit product is double-digit sum its *digits*

        num /= 10;
    }

    return sum;
}

void printCardType(int num_of_digits, int first_two_digits) 
{
    if (num_of_digits == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    } 
    else if (num_of_digits == 16 && first_two_digits >= 51 && first_two_digits <= 55)
    {
        printf("MASTERCARD\n");
    }
    else if ((num_of_digits == 13 || num_of_digits == 16) && (first_two_digits / 10) == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int main(void)
{
    long card_number = get_long("Number: "); // prompt for input
    int checksum = 0;
    
    
    checksum += calculate_checksum(card_number); // using Luhn's algorithm to calculate the checksum
    
    // if checksum is valid check card length and first two numbers and print card type accordingly
    if (checksum % 10 == 0)
    { 
        printCardType(countDigits(card_number), getFirst2Digits(card_number));
    }
    else 
    {
        printf("INVALID\n");
    }
}