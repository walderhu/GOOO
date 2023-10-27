#include <stdio.h>
#include <stdlib.h>
// #include <time.h>
#define BOARD_SIZE 3
#define EMPTY_SPACE ' '
typedef enum
{
    ONGOING,
    X_WON,
    O_WON,
    NOBODY,
    AI_WIN = 1,
    HUMAN_WIN = -1,
    DRAW = 0
} GameState;

char **creat_del_board(int);
void initialize_board(char **board);
void draw_board(char **board);
void input(char **board);
GameState check_game_state(char **board);

// доп реализация для pwe
int minimax(char **board, char player, int depth, int *best_move);
void apply_move(char **board, int move, char player);
void get_moves(char **board, int *moves, int *num_moves);
int evaluate(char **board);
void undo_move(char **board, int move);
void start_pwp();
void start_pwe();
void input_pwe(char **board);

int main()
{
    start_pwe();
    return 0;
}

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

    GameStatus = (GameStatus == -1) ? NOBODY : GameStatus; // проверка на ничью
    return GameStatus;
}

int minimax(char **board, char player, int depth, int *best_move)
{
    if (check_game_state(board))
    {
        return evaluate(board);
    }

    int moves[9];
    int num_moves = 0;
    get_moves(board, moves, &num_moves);

    int best_score = (player == 'X') ? -2 : 2;
    int current_move = -1;

    for (int i = 0; i < num_moves; i++)
    {
        int move = moves[i];
        apply_move(board, move, player);
        int score = minimax(board, (player == 'X') ? 'O' : 'X', depth + 1, NULL);
        if ((player == 'X' && score > best_score) || (player == 'O' && score < best_score))
        {
            best_score = score;
            current_move = move;
        }
        undo_move(board, move);
    }

    if (best_move != NULL)
    { // Если указатель best_move не равен NULL, установите его как текущий лучший ход.
        *best_move = current_move;
    }

    return best_score;
}

int evaluate(char **board)
{
    int GameStatus = -1;

    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++)
        if (board[i][0] != EMPTY_SPACE && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            GameStatus = (board[i][0] == 'X') ? AI_WIN : HUMAN_WIN;

    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++)
        if (board[0][j] != EMPTY_SPACE && board[0][j] == board[1][j] && board[1][j] == board[2][j])
            GameStatus = (board[0][j] == 'X') ? AI_WIN : HUMAN_WIN;

    // Check diagonals
    if (board[0][0] != EMPTY_SPACE && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        GameStatus = (board[0][0] == 'X') ? AI_WIN : HUMAN_WIN;

    if (board[0][2] != EMPTY_SPACE && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        GameStatus = (board[0][2] == 'X') ? AI_WIN : HUMAN_WIN;

    GameStatus = (GameStatus == -1) ? DRAW : GameStatus; // проверка на ничью
    return GameStatus;
}

void get_moves(char **board, int *moves, int *num_moves)
{
    *num_moves = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                moves[*num_moves] = i * BOARD_SIZE + j;
                (*num_moves)++;
            }
        }
    }
}
void apply_move(char **board, int move, char player)
{
    int i = move / 3;
    int j = move % 3;
    board[i][j] = player;
}
void undo_move(char **board, int move)
{
    int i = move / 3;
    int j = move % 3;
    board[i][j] = ' ';
}

void start_pwp()
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
}

void start_pwe()
{
    char **board = creat_del_board(0);
    initialize_board(board);

    while (!check_game_state(board))
    {
        input_pwe(board);
        draw_board(board);
    }
    creat_del_board(1);
}

void input_pwe(char **board)
{
    // srand(time(NULL));
    static int queue = 0;
    int x, y;

    if (queue % 2 == 0)
    {
        printf("Enter the coordinates of the row and column of the cell (1-3): ");
        if (scanf("%d %d", &x, &y) != 2 || x < 1 || x > BOARD_SIZE || y < 1 || y > BOARD_SIZE || board[x - 1][y - 1] != EMPTY_SPACE)
        {
            printf("Invalid input. Please try again.\n");
            return;
        }
        else
            board[x - 1][y - 1] = 'X';
    }
    else
    {
        int best_move = -1;
        minimax(board, 'O', 0, &best_move);

        if (best_move == -1)
        {
            printf("AI couldn't find the best move\n");
            return;
        }

        int i = best_move / BOARD_SIZE;
        int j = best_move % BOARD_SIZE;
        board[i][j] = 'O';
    }
    queue++;
}