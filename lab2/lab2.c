#include <stdio.h>
#include <string.h>

void verifyString(char str[])
{
    int original_len = strlen(str);
    char effective_str[100];
    int j = 0;

    // Validate characters and process epsilon 'e'
    for (int i = 0; i < original_len; i++)
    {
        // Check for characters other than '0', '1', and 'e'
        if (str[i] != '0' && str[i] != '1' && str[i] != 'e')
        {
            printf("INVALID\n");
            return;
        }

        // If character is 'e', skip
        // Otherwise, add it to our effective string
        if (str[i] != 'e')
        {
            effective_str[j] = str[i];
            j++;
        }
    }
    effective_str[j] = '\0';

    // print invalid if string length is < 2
    if (j < 2)
    {
        printf("INVALID\n");
        return;
    }

    // identify first and last character
    char first = effective_str[0];
    char last = effective_str[j - 1];

    // validate the string
    if ((first == '0' && last == '0') || (first == '1' && last == '1'))
    {
        printf("VALID\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int main()
{
    char input_string[100];

    printf("Enter string: ");
    if (scanf("%99s", input_string) == 1)
    {
        verifyString(input_string);
    }

    return 0;
}