from random import randint

def init_arr(dim):
    return list([] for _ in range(dim)) # initializing empty 2d arrays

# Didn't find any use cases for the dictionary so I implemeneted a random messenger :D
def get_random_message(key):
    random_messages = {
        "welcome_scene": ["Hello", "Hi", "Welcome", "Greetings", "Nice to see you"],
        "game_scene": ["You won't win, trust me", "Think twice", "Oh I see what you're doing..", "That won't help still..", "The challenge is on", "Ready to test your skills?"],
        "bye_scene": ["Thank you for playing! See you later", "Was a good game, GGs", "Fabulous! See you as soon as possible", "Goodbye!"],
        "win_scene": ["Lucky you won that one.", "You won.. Just don't get used to it.", "Next time you won't get a single point!", "Victory is sweet", "Impressive win!"],
        "loss_scene": ["Easy, good luck next time.", "Wasn't that hard to beat you", "Don't you think you should be practicing more by now?", "Oops, I won", "Better luck next time!"],
    }

    try:
        return random_messages[key][randint(0, len(random_messages[key]) - 1)]
    except KeyError:
        return f"No messages found for key: {key}"