from random import sample
from utility import init_arr, get_random_message

# Global Variables
dim=None
user_won=None
user_score=0
comp_score=0
user_total_score=0
comp_total_score=0

# Functions
def welcome(name):
    print(f"\n{get_random_message('welcome_scene')} {name}!\n")

def bye():
    print(f"{get_random_message('bye_scene')}\n")

def get_dimension():
    global dim

    user_input = input("Do you want to continue with 5x5 board? (y/n/q) ")
    while user_input not in ("y", "n", "q"):
        user_input = input("Invalid input. Enter 'y', 'n', or 'q'. ")

    if user_input == "y": dim = 5
    elif user_input == "n":
        ans = input("Enter your dimension: ")
        while not ans.isdigit() or int(ans) < 5: # must be in that order or if a non-digit entered will yield an error for converting to int
            ans = input("Invalid dimension. Must be a digit and more than or equal to 5.\nPlease enter again: ")
        dim = int(ans)
    else: # indicating the exit (user pressed "q")
        bye()
        return [], []
    return init_board(dim)

def init_board(dim):
    user_board = init_arr(dim)
    comp_board = init_arr(dim)
    create_boards(user_board, comp_board)
    return user_board, comp_board

def create_boards(user_board, comp_board):
    def create_board(board):
        randomized = sample(range(1, dim**2 + 1), dim**2)
        curr_row = 0

        for i in randomized:
            # appending each number in its correct position by shifting the ones after the required row length to the other nested list
            board[curr_row].append(i)
            if len(board[curr_row]) == dim: curr_row += 1

    create_board(user_board)
    create_board(comp_board)

def check_board(board):
    score=0

    # Row check
    for i in board:
        for j in i:
            if j != "X": break
        else: score+=1

    # Column check
    for i in range(dim):
        for j in board:
            if j[i] != "X": break
        else: score+=1
    
    # Diagonal check

    # checks if leftmost/rightmost variable bound is indeed an X, then continues the loop without breaking, so if ended successfully (enters else block) score+=1
    for j in board:
        if j[board.index(j)] == "X": continue
        break
    else: score+=1

    for j in board:
        if j[len(j) - 1 - board.index(j)] == "X": continue
        break
    else: score+=1

    return score

def cross_board(board, randomNumber):
    for i in range(dim):
        if randomNumber in board[i]:
            board[i][board[i].index(randomNumber)] = "X"

def print_boards(user_board, comp_board, inGame = False):
    def print_board(board, name):
        WIDTH=5
        sep=f"{'-' * (dim * (WIDTH + 1) - 2)}" # as dynamic as I possibly can make
        print(sep, f"{name:^{len(sep)}}", sep, sep="\n")
        for row in board:
            for num in row:
                print(f"{num:^{WIDTH}}", end=" ")
            print("\n")

    if inGame == True:
        print_board(user_board, "Your Turn")
        print(f"{get_random_message('game_scene')}\n")
        if user_won:
            print("Wait a sec.. You already beat me :(\n")
            print_board(comp_board, "Computer Board")
        else: print_board(comp_board,"Computer Turn")
    else:
        print_board(user_board, "Your Board")
        print_board(comp_board, "Computer Board")

def handle_number_validation(dim, crossed, name, user_board, comp_board):
    def handle_menu():
        choice = input("1. Save and Quit\n2. Quit without saving\n3. Save and Continue\n4. Continue without Saving\n- ")
        while choice not in ("1", "2", "3", "4"):
            choice = input("Invalid input. Enter '1', '2', '3', or '4' :) ")

        if choice in ("1", "3"): save_game(name, user_board, comp_board)
        if choice not in ("3", "4"): return 0
        else: return handle_number_validation(dim, crossed, name, user_board, comp_board)

    while True:
        user_input = input("Enter a number to cross or open menu (M/m): ")
        if user_input.lower() == 'm':
            return handle_menu()
        elif user_input.isdigit():
            num = int(user_input)
            if num in range(1, dim**2 + 1) and num not in crossed:
                crossed.append(num)
                return num
            else:
                print("Invalid input. Already crossed or out of range.\n")
        else:
            print("Invalid input. Must be a number or a key-binding (M/m)\n")

def play_game(name, user_board, comp_board):
    BINGO = "BINGO"
    PENDING_WORD = "_____"
    
    def check_win():
        global user_total_score, comp_total_score, user_won
        if user_score == len(BINGO):
            user_total_score+=1
            user_won=True
        if comp_score == len(BINGO): # not "elif"
            comp_total_score+=1
            user_won=False

    def handleTurns():
        global user_score, comp_score
        
        cross_board(user_board, chosen_number)
        user_score = check_board(user_board)
        check_win()

        if user_won: return # Don't switch to computer's turn if user already won

        cross_board(comp_board, chosen_number)
        comp_score = check_board(comp_board)
        check_win()

    if dim == None or user_board == []: return True

    crossed=[]
    print_boards(user_board, comp_board)

    while user_won == None:
        chosen_number = handle_number_validation(dim, crossed, name, user_board, comp_board)

        if chosen_number == 0:
            return True

        handleTurns()

        print_boards(user_board, comp_board, True)
        
        print(f"Your Progress: {(BINGO[:user_score] + PENDING_WORD[user_score:])}\nComp Progress: {BINGO[:comp_score] + PENDING_WORD[comp_score:]}")
    else:
        print(get_random_message("win_scene" if user_won else "loss_scene"))
        bye()
        return False
    
def save_game(file_name, user_board=[], comp_board=[]):
    def write_board(board):
         for row in board:
            for num in row:
                output = str(num)
                if row.index(num) != dim - 1:
                    output+=' '
                outFile.write(output)
            outFile.write("\n")

    not_finished = user_board and comp_board
    outFile = open(f"{file_name}.txt", "w")
    
    outFile.write("Scores:\n")
    outFile.write(f"{user_score} {comp_score} {user_total_score} {comp_total_score}\n" if not_finished else f"{user_total_score} {comp_total_score}\n")

    if not_finished:
        outFile.write("User Board:\n")
        write_board(user_board)

        outFile.write("Computer Board:\n")
        write_board(comp_board)

    print(f"Game saved successfully as '{file_name}.txt'")

def load_game():
    pass
    
def main(name = None):
    global dim, user_won, user_score, comp_score
    
    user_board, comp_board = [], []

    if name:
        user_board, comp_board = get_dimension()
    else:
        choice = input("1. Start a New Game\n2. Load a Saved Game\n3. Quit\n- ")
        while choice not in ("1", "2", "3"):
            choice = input("Invalid input. Enter '1', '2', or '3' :) ")

        if choice == "1":
            name = input(f"{get_random_message('welcome_scene')}, What's your name? ")
            welcome(name)
            user_board, comp_board = get_dimension()
        elif choice == "2":
            saved_game = load_game()
            if saved_game: # user didn't quit causing an empty return
                name, user_board, comp_board = saved_game 
                welcome(name)
            else: return
        else:
            bye()
            return

    while True:
        user_quit = play_game(name, user_board, comp_board)
        if user_quit: break

        print(f"Your Total Score: {user_total_score}\nComp Total Score: {comp_total_score}\n")

        choice = input("Do you want to save the game? (y/n) ")
        if choice.lower() == "y":
            save_game(name) # no need to save boards if game already ended

        # Resets all global variables except total score since the game will continue (but with different dimensions, and the score is zero).
        dim = None
        user_won = None
        user_score = 0
        comp_score = 0

        user_board, comp_board = [], []

        main(name)

# Main Program :>
main()
