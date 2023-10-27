#include "general.h"

int test_main()
{
    char **board = table(CREATE);
    int status;
    do
    {
        status = lobby();
        if (status == EXIT)
            break;
        initialize_board(board);
        while (!check_game_state(board) && status != EXIT)
        {
            if (status = (status == PVP ? input_pvp(board) : input_pve(board)) == EXIT)
                break;
            draw_board(board);
        }
        won(board, status);
        printf("Do you want to start over?\n1. Yes\n2. No\nAnswer: ");
        /*
        Вы  хотите выйти?
        1. Нет, продолжить игру
        2. Выйти в главное меню
        3. Выйти из игры
        */
        scanf("%d", &status);
    } while (status == AGAIN);
    table(DELETE);
    return 0;
}
