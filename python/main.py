import random

# Функция для отображения игрового поля
def display_board(board):
    print(' ' + board[1] + ' | ' + board[2] + ' | ' + board[3])
    print('-----------')
    print(' ' + board[4] + ' | ' + board[5] + ' | ' + board[6])
    print('-----------')
    print(' ' + board[7] + ' | ' + board[8] + ' | ' + board[9])

# Функция для создания копии игрового поля
def get_board_copy(board):
    return board[:]

# Функция для проверки возможных ходов
def get_possible_moves(board):
    moves = []
    for i in range(1, 10):
        if board[i] == ' ':
            moves.append(i)
    return moves

# Функция для проверки победителя
def check_winner(board, symbol):
    return (
        (board[1] == symbol and board[2] == symbol and board[3] == symbol) or
        (board[4] == symbol and board[5] == symbol and board[6] == symbol) or
        (board[7] == symbol and board[8] == symbol and board[9] == symbol) or
        (board[1] == symbol and board[4] == symbol and board[7] == symbol) or
        (board[2] == symbol and board[5] == symbol and board[8] == symbol) or
        (board[3] == symbol and board[6] == symbol and board[9] == symbol) or
        (board[1] == symbol and board[5] == symbol and board[9] == symbol) or
        (board[3] == symbol and board[5] == symbol and board[7] == symbol)
    )

# Функция для осуществления хода игрока
def make_player_move(board):
    while True:
        move = int(input('Ваш ход (1-9): '))
        if move in get_possible_moves(board):
            return move
        else:
            print('Недопустимый ход. Пожалуйста, повторите попытку.')

# Функция для осуществления хода компьютера
def make_computer_move(board, computer_symbol):
    if computer_symbol == 'X':
        player_symbol = 'O'
    else:
        player_symbol = 'X'
    
    # Алгоритм минимакса
    def minimax(board, depth, is_maximizing_player):
        if check_winner(board, computer_symbol):
            return 1
        elif check_winner(board, player_symbol):
            return -1
        elif len(get_possible_moves(board)) == 0:
            return 0
        
        if is_maximizing_player:
            best_score = float('-inf')
            for move in get_possible_moves(board):
                board_copy = get_board_copy(board)
                board_copy[move] = computer_symbol
                score = minimax(board_copy, depth + 1, False)
                best_score = max(score, best_score)
            return best_score
        else:
            best_score = float('inf')
            for move in get_possible_moves(board):
                board_copy = get_board_copy(board)
                board_copy[move] = player_symbol
                score = minimax(board_copy, depth + 1, True)
                best_score = min(score, best_score)
            return best_score
    
    best_move = None
    best_score = float('-inf')
    
    for move in get_possible_moves(board):
        board_copy = get_board_copy(board)
        board_copy[move] = computer_symbol
        score = minimax(board_copy, 0, False)
        
        if score > best_score:
            best_score = score
            best_move = move
    
    return best_move

# Основная игровая логика
def play_game():
    board = [' '] * 10
    player_symbol = 'X'
    computer_symbol = 'O'
    current_player = player_symbol

    while True:
        display_board(board)
        
        if current_player == player_symbol:
            move = make_player_move(board)
            board[move] = player_symbol
        else:
            move = make_computer_move(board, computer_symbol)
            board[move] = computer_symbol
        
        if check_winner(board, current_player):
            display_board(board)
            print('Игрок', current_player, 'победил!')
            break
        elif len(get_possible_moves(board)) == 0:
            display_board(board)
            print('Ничья!')
            break
        
        current_player = player_symbol if current_player == computer_symbol else computer_symbol

# Запуск игры
play_game()