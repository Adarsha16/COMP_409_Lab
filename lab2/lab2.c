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
        // If character is not a, b, or e return.
        if (str[i] != 'a' && str[i] != 'b' && str[i] != 'e')
        {
            printf("INVALID\n");
            return;
        }

        // If character is 'e', ignore it
        // Else, add it to our effective string
        if (str[i] != 'e')
        {
            effective_str[j] = str[i];
            j++;
        }
    }
    effective_str[j] = '\0';

    // Check length of the effective string
    if (j < 2)
    {
        printf("INVALID\n");
        return;
    }

    // Identify first and last character
    char first = effective_str[0];
    char last = effective_str[j - 1];

    // Check against the regular expression structure
    if ((first == 'a' && last == 'b') || (first == 'b' && last == 'a'))
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