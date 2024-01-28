from random import randint, sample
from utility import init_arr, generateRandomNumber, wait

# Global Variables
dim=None
state=None # 0 for loss, 1 for win
randomMessages = {"randomNumberScene": ["Where's that number on my board..", "I can't find it..", "let me see.."],
                    "endGameScene":["Thank you for playing! See you as soon as possible", "It was a good game, GG", "That was easy.. See you soon"]}

# Functions
def handleReset(name):
    global dim, state

    # if state == 0:
    #     message = "Lose again "
    # else:
    #     message = "Give me another chance "
    message = "Lose again " if state == 0 else "Give me another chance " # Please no 0.5/5
    ans = input(f"{message}or quit （　＾ω＾）? (y/n)")

    while ans not in ("y", "n"):
        ans = input("Invalid input. Enter 'y' or 'n' :) ")
    if ans == "y":
        dim = None
        state = None
        main(name)
    else: bye(name)

def welcome(name):
    print(f"\nWelcome {name}!", end=f"\n")
    return name

def bye(name):
    print(f"\n{randomMessages['endGameScene'][randint(0, len(randomMessages['endGameScene']) - 1)]} {name}\n")
    
def handle_dims():
    ans = input("Do you want to continue with 5x5 board? (y/n/q) ")
    while ans not in ("y", "n", "q"):
        ans = input("Invalid input. Enter 'y', 'n', or 'q'. ")
    # if ans == "y":
    #     return 5
    # elif ans == "n":
    #     return int(input("Enter your dimension: "))
    # return dim # which is None
    return 5 if ans == "y" else int(input("Enter your dimension: ")) if ans == "n" else dim # which is None

def init(dim):
    user_board = init_arr(dim)
    comp_board = init_arr(dim)

    create_boards(user_board, comp_board)

    return user_board, comp_board # Multiple returns, acts as a tuple

def create_boards(user_board, comp_board):
    def create_board(board):
        randomized = sample(range(1, dim**2 + 1), dim**2)
        curr_row = 0
        # appending each number in its correct position by shifting the ones after the required row length to the other nested list
        for i in randomized:
            board[curr_row].append(i)
            if len(board[curr_row]) == dim: curr_row += 1

    create_board(user_board)
    create_board(comp_board)

def check_board(board, userTurn):
    pass

def cross_board(board, randomNumber):
    for i in range(0, dim):
        if randomNumber in board[i]:
            board[i][board[i].index(randomNumber)] = "X"

    return state

def print_boards(user_board, comp_board, isPlaying = False):
    def print_board(board, name):
        print(sep, f"{name:^{len(sep)}}", sep, sep="\n")
        for row in board:
            for num in row:
                print(f"{num:^{WIDTH}}", end=" ")
            print("\n")
    WIDTH=5
    sep=f"{'-' * (dim * (WIDTH + 1) - 2)}" # as dynamic as I possibly can make

    if isPlaying == True:
        print_board(user_board, "Your Turn")
        print(randomMessages["randomNumberScene"][randint(0, len(randomMessages["randomNumberScene"]) - 1)], end="\n")
        wait()
        print("\n")
        if state == 1:
            print("Wait a minute.. ")
            print("I already lost :O \n")
            print_board(comp_board, "My board")
        else: print_board(comp_board,"My Turn")
    else:
        print_board(user_board, "Your Board")
        print_board(comp_board, "My Board")

def play(user_board, comp_board, name):
    def handleInput(message):
        key = input(message)
        while key != "":
            key = input("It's literally labeled 'Enter', not on right side of your non-mechanical-membrane keyboard :P ")

    def handleTurns(user_board, comp_board):
        cross_board(user_board, randomNumber)
        check_board(user_board, True)

        if state == 1: return # Don't switch to computer's turn if user already won 

        cross_board(comp_board, randomNumber)
        check_board(comp_board, False)

    crossed=[]
    print_boards(user_board, comp_board)

    while state == None:
        handleInput("Press 'Enter' to choose a random number.. ")

        randomNumber = generateRandomNumber(dim, crossed)

        handleInput(f"Press 'Enter' again to cross '{randomNumber}' out of your board.. ")
        
        handleTurns(user_board, comp_board)

        print_boards(user_board, comp_board, True)
    # if state == 1: print("Lucky you won that one!")
    # else: print("Got ya! I won :) \nGoodluck next time. ")
    print("Lucky you won that one!" if state == 1 else "Got ya! I won :) \n Goodluck next time. ")
    bye(name)

def main(name = None):
    global dim
    if name == None:
        name = input("Hi, What's your name? ")
        welcome(name)
        print("And your age? ", end=" ") # end=" " so it stays on the same line, preserving its disguise as the input() function
        wait(3)
        print("\nJoking :D ")

    dim = handle_dims() # dim is the return value of the function handle_dims (always integer) 
    if not dim: # a flag indicating the exit (user pressed "q") 
        bye(name)
        return

    user_board, comp_board = init(dim) # destructures the tuple-like return value from init()

    play(user_board, comp_board, name)
    handleReset(name)

# Main Program :>
main()
