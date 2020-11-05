# text-adventure-clue
In this project, I had 5 different pointer types, the room, the character, the item, the avatar itself, and the
murder. Each of them were declared in their respective header files, except for avatar which was in character.h
and murder was declared in adventure.c. Every time I create one of these structs, it is dynamically allocated
because I use the malloc function in my building methods(these are all freed at the very end). The program
starts by randomizing the rooms, items, and characters, it then prompts the user to type a command. The user
types in a command and the program matches it to a command word by word. Once it finds the command the user
wanted, it then calls upon the correct function. The program ends when the player exceeds 10 guesses or gets the
3 matches that are contained within the murder struct(this just holds the guilty room, character and item which
is randomly assigned). To take in text input specifically, I had a buffer array which got the stdin from a
getline function. I then split each word up in the buffer array as it need be. To randomize everything I gave
each room a name via randomly choosing from an array, then I used the same method to add characters and items to
the room making sure there was only one of each max in a room. I then linked each room to form a 3x3 grid and
placed in the starting room, which is the very middle room. Each room had a dummy pointer for items and characters so I could contain multiple of them via linked list. Having the dummy also made it possible for me to add and remove items   from the list per command.

video link: https://youtu.be/qxyoTSxHtSM
