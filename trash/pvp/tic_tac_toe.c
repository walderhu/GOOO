#include "tic_tac_toe.h"

char **creat_del_board(int command)
{
    static char **board = NULL;
    if (command == 0)
    {
        board = (char **)calloc(BOARD_SIZE, sizeof(char *));
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            board[i] = (char *)calloc(BOARD_SIZE, sizeof(char));
            for (int j = 0; j < BOARD_SIZE; j++)
                board[i][j] = EMPTY_SPACE;
        }
    }
    else if (command == 1)
    {
        for (int i = 0; i < BOARD_SIZE; i++)
            free(board[i]);
        free(board);
        board = NULL;
    }
    return board;
}

void initialize_board(char **board)
{
    for (size_t x = 0; x < BOARD_SIZE; x++)
        for (size_t y = 0; y < BOARD_SIZE; y++)
            board[x][y] = EMPTY_SPACE;
}

void draw_board(char **board)
{
    // system("clear");
    for (size_t x = 0; x < BOARD_SIZE; x++)
    {
        x == 0 ? printf(" ----------- \n") : printf("|---+---+---|\n");
        for (size_t y = 0; y < BOARD_SIZE; y++)
            (y == BOARD_SIZE - 1) ? printf("| %c |\n", board[x][y]) : printf("| %c ", board[x][y]);
        if (x == BOARD_SIZE - 1)
            printf(" ----------- \n");
    }
}

void input(char **board)
{
    // srand(time(NULL));
    static int queue = 0;
    int x, y;
    printf("Enter the coordinates of the row and column of the cell (1-3): ");
    if (scanf("%d %d", &x, &y) != 2 || x < 1 || x > BOARD_SIZE || y < 1 || y > BOARD_SIZE || board[x - 1][y - 1] != EMPTY_SPACE)
        printf("Invalid input. Please try again.\n");
    else
        board[x - 1][y - 1] = ((queue++) % 2 == 0) ? 'X' : 'O';
}

GameState check_game_state(char **board)
{
    // Check for draw
    int GameStatus = -1;
    for (int i = 0; i < BOARD_SIZE; i++) 
        for (int j = 0; j < BOARD_SIZE; j++) 
            if (board[i][j] == EMPTY_SPACE) 
                GameStatus = ONGOING;

    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++) 
        if (board[i][0] != EMPTY_SPACE && board[i][0] == board[i][1] && board[i][1] == board[i][2]) 
            GameStatus = (board[i][0] == 'X') ? X_WON : O_WON;

    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++) 
        if (board[0][j] != EMPTY_SPACE && board[0][j] == board[1][j] && board[1][j] == board[2][j]) 
            GameStatus = (board[0][j] == 'X') ? X_WON : O_WON;

    // Check diagonals
    if (board[0][0] != EMPTY_SPACE && board[0][0] == board[1][1] && board[1][1] == board[2][2]) 
        GameStatus = (board[0][0] == 'X') ? X_WON : O_WON;
    
    if (board[0][2] != EMPTY_SPACE && board[0][2] == board[1][1] && board[1][1] == board[2][0]) 
        GameStatus = (board[0][2] == 'X') ? X_WON : O_WON;
    
    GameStatus = (GameStatus == -1) ? DRAW : GameStatus; // проверка на ничью
    return GameStatus;
}