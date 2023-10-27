#include "tic_tac_toe.h"
int main()
{
    char **board = creat_del_board(0);
    initialize_board(board);
    while (!check_game_state(board))
    {
        input(board);
        draw_board(board);
        if (getchar() == 'q')
            break;
    }
    creat_del_board(1);
    return 0;
}