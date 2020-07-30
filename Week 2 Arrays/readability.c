#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>


/** The Coleman–Liau index is a readability test 
 * The Coleman–Liau index is calculated with the following formula:
 * Coleman-Liau index = 0.0588*L - 0.296*S - 15.8
 * Here, L is the average number of letters per 100 words in the text and
 * S is the average number of sentences per 100 words in the text.
 */
int main(void)
{
    string text = get_string("Text: ");
    int letters = 0, sentences = 0;
    int words = 1; // if there are no spaces we have exactly one word if we find 1 space we have two words etc
    
    while (*text != '\0')
    {
        if (islower(*text) || isupper(*text))
        {
            ++letters;
        }
        else if (*text == ' ')
        {
            ++words;
        }
        else if (*text == '.' || *text == '!' || *text == '?')
        {
            ++sentences;
        }
        
        ++text;
    }
    
    float index = 0.0588 * (100 * (float) letters / (float) words) - 0.296 * (100 * (float) sentences / (float) words) - 15.8;
    
    if (index < 16 && index >= 1)
    {
        printf("Grade %d\n", (int) round(index));
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
}