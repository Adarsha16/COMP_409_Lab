#include <stdio.h>
#include <string.h>

void removeLeftRecursion(char production[])
{
    char non_terminal = production[0];
    char alpha[50], beta[50];
    int i = 3; // Start reading after "A->"

    // Check if RHS[0] == LHS[0]
    if (production[i] == non_terminal)
    {
        int a_idx = 0, b_idx = 0;
        i++; // Skip the recursive non-terminal
        // Extract alpha
        while (production[i] != '|' && production[i] != '\0')
        {
            alpha[a_idx++] = production[i++];
        }
        alpha[a_idx] = '\0';
        // Extract beta
        if (production[i] == '|')
        {
            i++; // Skip '|'
            while (production[i] != '\0')
            {
                beta[b_idx++] = production[i++];
            }
        }
        beta[b_idx] = '\0';

        printf("%c -> %s%c'\n", non_terminal, beta, non_terminal);
        printf("%c' -> %s%c' | e\n", non_terminal, alpha, non_terminal);
    }
    else
    {
        printf("%s\n", production);
    }
}
int main()
{
    int n;
    char productions[10][100];

    printf("Enter number of productions: ");
    if (scanf("%d", &n) != 1)
        return 1;
    for (int i = 0; i < n; i++)
    {
        printf("Enter production %d (Format A->Aalpha|beta): ", i + 1);
        scanf("%s", productions[i]);
    }
    printf("\nGrammar after removing left recursion:\n\n");
    // Repeat for each production
    for (int i = 0; i < n; i++)
    {
        removeLeftRecursion(productions[i]);
    }
    printf("\n");
    return 0;
}