#include <stdio.h>
#define TRUE 1
#define A 1
#define B 2
#define C 3
int main()
{
    printf("\033[2J");   // Clear the entire screen
    printf("\033[0;0f"); // Move cursor to the top left hand corner
    printf("Select Module:\n %d. Module A\n %d. Module B\n %d. Module C\n", A, B, C);
    //
    float answer;
    while (TRUE)
    {
        printf("Answer: ");
        if (scanf("%f", &answer) && (answer == A || answer == B || answer == C))
        {
            printf("Well done\n");
            break;
        }
        // Clear input buffer
        while (getchar() != '\n')
            ;
        static int a = 0;
        if ((a++) == 0)
            printf("\n");

        for (int i = 0; i < 2; i++)
        {
            printf("\033[2K"); // Clear the current line
            printf("\033[1A"); // Move the cursor up one line
        }
        printf("Invalid input, try again!\n");
    }
    return 0;
}