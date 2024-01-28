from constants import WORD, MULTIPLIER, TURN_DELAY, RANDOM_MESSAGES_DICT
from random import sample, randint, choice
from time import sleep

# Global Variables
user_won = None
user_score, comp_score, user_total_score, comp_total_score = 0, 0, 0, 0

def get_random_message(key):
    try:
        return RANDOM_MESSAGES_DICT[key][randint(0, len(RANDOM_MESSAGES_DICT[key]) - 1)]
    except KeyError:
        return f"No messages found for key: {key}"

def set_difficulty():
    pass

def set_dimension():
    def create_board(): # dim variable is assigned in the parent function before calling
        randomized = sample(range(1, dim**2 + 1), dim**2) # generates the random unique list
        return [randomized[i:i+dim] for i in range(0, len(randomized), dim)] # adds from the sample nested lists with the dimension as a sign for the end of the nested list (row)

    choice = input(f"Do you want to continue with the standard {len(WORD)}x{len(WORD)} board? (y/n/q) ")
    while choice not in ("y", "n", "q"):
        choice = input("Invalid input. Enter 'y', 'n', or 'q'. ")
    if choice == "n":
        user_input = input("Enter your dimension: ")
        while not (user_input.isdigit() and int(user_input) >= len(WORD)): # must be in that order or if a non-digit entered will yield an error for converting to int
            user_input = input(f"Invalid dimension. Must be a digit and more than or equal to {len(WORD)}.\nPlease enter again: ")
        dim = int(user_input)
    elif choice == "q": return [], [] # indicating the exit
    else: dim = len(WORD)
     
    return create_board(), create_board()

def play_game(name, difficulty, crossed_dict, user_board, comp_board):
    global user_won, user_total_score, comp_total_score
    dim = len(user_board)

    def print_boards(user_board, comp_board):
        pending_word = "_" * len(WORD)
        def print_board(board, name):
            sep=f"{'-' * (dim * (len(WORD) + 1) - 2)}" # as dynamic as possible
            print(sep, f"{name:^{len(sep)}}", sep, sep="\n")
            for row in board:
                for num in row:
                    print(f"{num:^{len(WORD)}}", end=" ")
                print("\n")

        print_board(user_board, "Your Board")
        
        if user_won: print("Wait a sec.. You already beat me :(\n")

        print_board(comp_board, "My Board")

        if len(crossed_dict): print(f"{get_random_message('game_scene')}\n") # if not first print of boards (no crossed numbers)

        print(f"Your Progress: {(WORD[:user_score] + pending_word[user_score:])}\nComp Progress: {WORD[:comp_score] + pending_word[comp_score:]}")

    def handle_number_validation():
        def handle_menu():
            choice = input("1. Save and Quit\n2. Quit without saving\n3. Save and Continue\n4. Continue without Saving\n- ")
            while choice not in ("1", "2", "3", "4"):
                choice = input("Invalid input. Enter '1', '2', '3', or '4'")

            if choice in ("1", "3"): save_game(name, difficulty, crossed_dict, user_board, comp_board)
            if choice not in ("3", "4"): return 0
            else: return handle_number_validation()

        while True:
            user_input = input("Enter a number to cross or open menu (M/m): ")
            if user_input.lower() == 'm': return handle_menu()

            if user_input.isdigit():
                num = int(user_input)
                if num in range(1, dim**2 + 1) and num not in crossed_dict.values(): return num
                else: print("Invalid input. Already crossed or out of range.\n")
            else: print("Invalid input. Must be a number or a key-binding (M/m)\n")

    def check_win():
        global user_won, user_total_score, comp_total_score

        if user_won == None:
            if user_score == len(WORD):
                user_total_score+=1
                user_won = True
            if comp_score == len(WORD): # not elif
                comp_total_score+=1
                user_won = False

    def handle_turn(chosen_number, comp_turn):
        global user_score, comp_score
        
        def cross_board(board, comp_turn_to_cross = False):
            for i in range(dim):
                if chosen_number in board[i]:
                    index_of_chosen_number = board[i].index(chosen_number)
                    board[i][index_of_chosen_number] = "X"
                    if comp_turn_to_cross: crossed_dict[(index_of_chosen_number, i)] = chosen_number # only if it is the computer's turn to cross the boards, add a pair tuple representing x and y coordinates (tracking computer's crosses  coordinates only)
                    break

        def check_board(board):
            score = 0

            # Row check
            '''
            checks all rows if any of them is not crossed break else adds a point
            '''
            for i in board:
                for j in i:
                    if j != "X": break
                else: score += 1

            # Column check
            '''
            checks all nested lists with current index (the column) if any of them is not crossed break else adds a point
            '''
            for i in range(dim):
                for j in board:
                    if j[i] != "X": break
                else: score += 1

            # Diagonal check
            '''
            if the leftmost/rightmost variable bound is crossed, then continues the loop without breaking, if ended successfully (with the diagonal crossed), it adds a point
            '''
            for j in board:
                if j[board.index(j)] == "X": continue
                break
            else: score+=1

            for j in board:
                if j[len(j) - 1 - board.index(j)] == "X": continue
                break
            else: score += 1

            return score

        cross_board(user_board)
        user_score = check_board(user_board)
        check_win()

        if user_won == None: # explicitly, because "if not user_won" works for both the None (no winner) which is the intended and also for the False (computer won, but in this case, by me (meaning that I crossed for him the last one)) which is the not intended
            cross_board(comp_board, True)
            if comp_turn: print(f"I chose to cross '{chosen_number}'\n")
            comp_score = check_board(comp_board)
            check_win()

        if not comp_turn: print("\n")
        print_boards(user_board, comp_board)

    def make_user_move():
        chosen_number = handle_number_validation()

        if chosen_number == 0: return True

        handle_turn(chosen_number, False)

    def make_comp_move():
        pass

    if not dim: return True

    print_boards(user_board, comp_board)

    while user_won == None:
        print(f"\n\n{'Your Turn..' if len(crossed_dict) else 'You go first..':^{len(WORD)**2}}\n\n")
        user_quit = make_user_move()

        if user_quit: break

        if user_won != None: continue # if game ended, skip the computer move

        print(f"\n\n{'My Turn':^{len(WORD)**2}}\n\n")
        
        if len(crossed_dict): print(f"{get_random_message('thinking_scene')}")
        
        sleep(randint(TURN_DELAY[0], TURN_DELAY[1]) / 100.0) # Generates a random float

        make_comp_move()
    else:
        print(f"\n{get_random_message('win_scene' if user_won else 'loss_scene')}\n")
        return False
    return True
    
def save_game(file_name, difficulty=None, crossed_dict={}, user_board=[], comp_board=[]):
    def write_board(board):
         for row in board:
            for num in row:
                output = str(num)
                if row.index(num) != len(user_board) - 1: output+=' '
                outFile.write(output)
            outFile.write("\n")

    not_finished = user_board and comp_board
    outFile = open(f"{file_name}.txt", "w")
    
    outFile.write("Scores:\n")
    outFile.write(f"{user_score} {comp_score} {user_total_score} {comp_total_score}\n" if not_finished else f"{user_total_score} {comp_total_score}\n")

    if not_finished:
        outFile.write("Difficulty:\n")
        outFile.write(f"{difficulty}\n")
    
        outFile.write("Crossed Dictionary:\n")
        for coordinates, number in crossed_dict.items():
            outFile.write(f"{coordinates[0]},{coordinates[1]}:{number}\n")

        outFile.write("User's Board:\n")
        write_board(user_board)

        outFile.write("Computer's Board:\n")
        write_board(comp_board)

    print(f"Game saved successfully as '{file_name}.txt'")

def load_game():
    global user_score, comp_score, user_total_score, comp_total_score

    while True:
        try:
            name = input("Enter your name associated with the saved game or quit (q/Q): ")
            if name.lower() == 'q': return

            with open(f"{name}.txt", "r") as fileObj:
                lines = fileObj.read().split("\n") # by splitting we excluded the use of rstrip()
                is_finished = len(lines) == 3 # if game is already finished, there will be only three items, 1st is the scores string, the 2nd is the scores values and same with the difficulty, lastly is the sentinel returned due to the end of file. Which means that no boards have been saved after that which is only not saved because the game is already finished (saving boards after the game has ended is useless)
                first_line = lines[1].split(" ")
                crossed_dict = {} # must be referenced here and doesn't depend on the upcoming conditionals as opposed to boards 

                if is_finished:
                    user_score, comp_score = 0, 0
                    user_total_score, comp_total_score = int(first_line[0]), int(first_line[1])
                    user_board, comp_board = set_dimension()

                    if not user_board: return # indicating the exit
                    difficulty = set_difficulty()
                else:
                    user_score, comp_score = int(first_line[0]), int(first_line[1])
                    user_total_score, comp_total_score = int(first_line[2]), int(first_line[3])
                    difficulty = float(lines[3])

                    crossed_dict_lines = lines[5: lines.index("User's Board:")]
                    for line in crossed_dict_lines:
                        if line:
                            coordinates, number = line.split(":")
                            x_str, y_str = coordinates.split(",")
                            x = int(x_str)
                            y = int(y_str)
                            crossed_dict[(x, y)] = int(number)

                    dim = (len(lines) - 8 - len(crossed_dict_lines)) // 2 # getting length of the two boards which needs the subtraction of titles, scores, difficulty, crossed dictionary and the sentinel. Total is 8 and dividing it by two yields the dimension of one board.

                    user_board_lines = lines[5 + len(crossed_dict_lines) + 1: 5 + len(crossed_dict_lines) + 1 + dim]
                    comp_board_lines = lines[5 + len(crossed_dict_lines) + 1 + dim + 1: -1]

                    # nested-list comprehension to add integers or a cross 'X' based on the lines
                    user_board = [[int(x) if x != 'X' else x for x in line.split()] for line in user_board_lines]
                    comp_board = [[int(x) if x != 'X' else x for x in line.split()] for line in comp_board_lines]
                break
        except FileNotFoundError:
           print(f"Save files are case-sensitive. File '{name}' not found. Please try again later.")
        except:
            print("The save file may be corrupted or outdated. Sorry for the inconvenience.")

    return name, difficulty, crossed_dict, user_board, comp_board

def init_vars():
    user_won = None
    user_board, comp_board = [], []
    user_score, comp_score = 0, 0
    return user_won, user_score, comp_score, user_board, comp_board

def main(name = None):
    global user_won, user_score, comp_score

    def welcome(name):
        print(f"\n{get_random_message('welcome_scene')} {name}!\n")

    def bye():
        print(f"{get_random_message('bye_scene')}\n")

    crossed_dict = {}

    if name:
        user_board, comp_board = set_dimension()
        if not user_board: return
        difficulty = set_difficulty()
    else:
        choice = input("1. Start a New Game\n2. Load a Saved Game\n3. Quit\n- ")
        while choice not in ("1", "2", "3"):
            choice = input("Invalid input. Enter '1', '2', or '3'")

        if choice == "1":
            name = input(f"{get_random_message('welcome_scene')}, What's your name? ")

            user_board, comp_board = set_dimension()
            if not user_board: return

            difficulty = set_difficulty() 
            welcome(name)
        elif choice == "2":
            saved_game = load_game()
            if saved_game:
                name, difficulty, crossed_dict, user_board, comp_board = saved_game # must be in the same order of the returned tuple
                welcome(name)
            else: # user quitted in load_game func causing an empty return
                bye()
                return
        else: # user quitted by '3'
            bye()
            return 

    while True:
        user_quit = play_game(name, difficulty, crossed_dict, user_board, comp_board)
        if user_quit: break

        print(f"Your Total Score: {user_total_score}\nMy Total Score: {comp_total_score}\n")

        choice = input("Do you want to save the game? (y/n) ")
        if choice.lower() == "y": save_game(name) # less args; no need to save boards, crossed dictionary, and difficulty if the game is already ended

        user_won, user_score, comp_score, user_board, comp_board = init_vars() # resets global variables before making the recursive call

        main(name)  
    bye()

# Main Program :>
main()
