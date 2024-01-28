import random 

# Global Variables
dim=None

# Functions
def welcome(name):
    print(f"\nWelcome {name}!", end=f"\n")
    return name

def handle_dims():
    ans = input("Do you want to continue with 5x5 board? (y/n/q) ")
    while ans not in ("y", "n", "q"):
        ans = input("Invalid input. Please enter 'y', 'n', or 'q'.")
    if ans == "y":
        return 5
    elif ans == "n":
        return int(input("Enter your dimension: "))
    return dim # which is None

def init_arr(dim):
    return list([] for _ in range(dim)) # initializing empty 2d arrays

def init(dim):
    user_board = init_arr(dim)
    comp_board = init_arr(dim)

    create_board(user_board)
    create_board(comp_board)

    return user_board, comp_board

def create_board(board):
    square = dim**2
    randomized = random.sample(range(1, square + 1), square)
    curr_row = 0
    # appending each number in its correct position by shifting the ones after the required row length to the other nested list
    for i in randomized:
        board[curr_row].append(i)
        if len(board[curr_row]) == dim: curr_row += 1

def print_board(name, board):
    WIDTH=5
    sep=f"{'-' * (dim * (WIDTH + 1) - 2)}" # as dynamic as I possibly can make

    print(sep, f"{name:^{len(sep)}}", sep, sep="\n")
    for row in board:
        for num in row:
            print(f"{num:^{WIDTH}}", end=" ")
        print()
    print()

def main():
    global dim
    name = input("Enter your name: ")
    welcome(name)

    dim = handle_dims() # dim is the return value of the function handle_dims (always integer) 
    if not dim: # a flag indicating the exit (user pressed "q") 
        print(f"\nThank you for playing! See you later, {name}\n")
        return # empty return, exits the parent function "main" without continuing down the statements

    user_board, comp_board = init(dim)

    print_board("Your Board", user_board)
    print_board("Computer Board", comp_board)

# Main Program :>
main()
