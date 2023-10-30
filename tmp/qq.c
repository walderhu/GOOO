#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int get_user_input(int num_options, ...);

int main()
{
    printf("User: %d\n", get_user_input(7, 1, 2, 3, 99, -134, 777, 823480));
    return 0;
}

int get_user_input(int num_options, ...)
{
    while (1)
    {
        float answer;
        va_list options;
        va_start(options, num_options);

        printf("Answer: ");
        if (scanf("%f", &answer) && answer == (int)answer && (getchar() == '\n' || getchar() == ' '))
        {
            for (int i = 0; i < num_options; i++)
                if (answer == va_arg(options, int))
                {
                    va_end(options);
                    return answer;
                }
        }
        else
            while (getchar() != '\n')
                ;
        printf("\033[1A"); // Move the cursor up one line
        printf("\033[2K"); // Clear the current line
        printf("Invalid input, try again!\n");
        sleep(1);
        printf("\033[1A"); // Move the cursor up one line
        printf("\033[2K"); // Clear the current line
        va_end(options);
    }
}