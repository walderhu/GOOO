#include "general.h"

int menu()
{
    system("clear");
    printf("Select an action:\n");
    printf(" %d. Continue the game\n", CONTINUE_GAME);
    printf(" %d. Start over\n", START_OVER);
    printf(" %d. Exit to the lobby\n", EXIT_TO_LOBBY);
    printf(" %d. Exit the game\n", EXIT_THE_GAME);

    float answer;
    while (TRUE)
    {
        printf("Answer: ");
        if (scanf("%f", &answer) && answer == (int)answer && (answer == CONTINUE_GAME || answer == START_OVER || answer == EXIT_TO_LOBBY || answer == EXIT_THE_GAME))
            break;
        // Clear input buffer
        while (getchar() != '\n')
            ;
        printf("Invalid input, try again!\n");
    }
    system("clear");
    return answer;
}

int input(char **board, GAME_t *status)
{
    if (status->game == PVP)
    {
        status->tmp = input_pvp(board);
        if (status->tmp == MENU)
            status->menu = status->tmp;
        else
            status->game = status->tmp;
    }
    else if (status->game == PVE)
    {
        status->tmp = input_pve(board);
        if (status->tmp == MENU)
            status->menu = status->tmp;
        else
            status->game = status->tmp;
    }
    else
        return status->tmp;

    if (status->menu == MENU)
        status->menu = menu();

    if (status->menu == START_OVER)
    {
        initialize_board(board);
        status->menu = 0;
        // printf("%s mode\n", (status->game == PVP) ? "PVP" : "PVE");
    }

}