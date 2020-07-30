#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool containOnlyAlphabetLetters(string key)
{
    while (*key != '\0')
    {
        if (!isalpha(*key))
        {
            return false;
        }
        ++key;
    }
    return true;
}

bool containEachLetterOnce(string key)
{
    bool flag = false; 
    for (int i = 0; i < strlen(key); ++i)
    { 
        for (int j = i + 1; j < strlen(key); ++j)
        { 
            if (key[i] == key[j]) 
            {
                return false;
            } 
        } 
    } 
    return true; 
}

char cipherLetter(string key, char letter)
{
    int index = 0;

    if (isupper(letter))
    {
        index = letter - 'A';
        return toupper(key[index]);
    }
    else if (islower(letter))
    {
        index = letter - 'a';
        return tolower(key[index]);
    }
    return letter;
}


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    
    string key = argv[1];
    
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (!containOnlyAlphabetLetters(key))
    {
        printf("Key must only contain alphabetic characters\n");
        return 1;
    }
    else if (!containEachLetterOnce(key))
    {
        printf("Key must only contain each letter exactly once\n");
        return 1;
    }
    
    string plaintext = get_string("plaintext: ");
    while (strlen(plaintext) <= 0)
    {
        plaintext = get_string("plaintext: ");
    }
    int len = strlen(plaintext);
    char ciphertext[len];
    
    for (int i = 0; plaintext[i] != '\0'; ++i)
    {
        ciphertext[i] = cipherLetter(key, plaintext[i]);
    }
    ciphertext[len] = '\0';
    
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}