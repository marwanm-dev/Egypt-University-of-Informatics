from random import randint, random
from time import sleep

def init_arr(dim):
    return list([] for _ in range(dim)) # initializing empty 2d arrays

def generateRandomNumber(dim, crossed):
    randomNumber = randint(1, dim**2)
    while randomNumber in crossed:
        randomNumber = randint(1, dim**2)

    crossed.append(randomNumber)
    return randomNumber

def wait(multiplier = 2):
    sleep(random() * multiplier)