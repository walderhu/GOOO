#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int get_user_input(int num_options, ...);
void delete_line();

int main()
{
    get_user_input(3, 1, 2, 3);
    delete_line();
    puts("DONE!");
    return 0;
}

int get_user_input(int num_options, ...)
{
    system("clear");
    while (1)
    {
        va_list options;
        va_start(options, num_options);
        int answer;
        char input[256];
        printf("Answer: ");
        if (fgets(input, sizeof(input), stdin) != NULL)
            if (answer = strtol(input, NULL, 10))
                for (int i = 0; i < num_options; i++)
                    if (answer == va_arg(options, int))
                        return answer;
        delete_line();
        printf("Invalid input, try again!\n");
        sleep(1);
        delete_line();
        va_end(options);
    }
}

void delete_line()
{
    printf("\033[1A"); // Move the cursor up one line
    printf("\033[2K"); // Clear the current line
}
