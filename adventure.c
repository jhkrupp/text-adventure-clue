#include<stdio.h>
#include<string.h>
#include "character.h"
#include "items.h"
#include "room.h"
#include<time.h>
#include<stdlib.h>

//shows how many guesses the player has used
static int guessCounter = 0;

//struct that holds the murder event items which the player is trying to guess
struct Murder {
    struct Room* room;
    struct Item* item;
    struct Character* person;
};

struct Murder* murder(struct Room *room, struct Item *item, struct Character *person) {
    struct Murder *event = (struct Murder*) malloc(sizeof(struct Murder));
    if (event == NULL) {
        return NULL;
    }
    event->room = room;
    event->item = item;
    event->person = person;
    return event;
}

void look(struct Room *room) {
    //check if the room has people
    if (room->people->others == NULL) {
        printf("no one in the room\n");
    } else {
        struct Character* cur = npc("cur", "cur", room->people->others, NULL);
        printf("The people in this room: \n");
        while(cur->others != NULL) {
            printf("%s\n", cur->others->name);
            cur = cur->others;
        }
    }
    //check if the room has items
    if (room->items->next == NULL) {
        printf("No items in this room\n");
    } else {
        struct Item* stuff = item("cur", "cur", room->items->next);
        printf("The items in the room:\n");
        while(stuff->next != NULL) {
            printf("%s\n", stuff->next->name);
            stuff = stuff->next;
        }
    }
    //checks each direction
    if (room->north != NULL) {
        printf("To the north: %s\n", room->north->description);
    }
    if (room->south != NULL) {
        printf("To the south: %s\n", room->south->description);
    }
    if (room->east != NULL) {
        printf("To the east: %s\n", room->east->description);
    }
    if (room->west != NULL) {
        printf("To the west: %s\n", room->west->description);
    }
}
void help() {
    printf("Here is a list of commands:\n list \n look \n go DIRECTION \n take item \n drop item \n clue CHARACTER \n inventory \n");
}

void list() {
    printf("List of rooms: \n The Kitchen \n Master Bedroom \n Bathroom \n Indoor Pool \n Planetarium \n Gaming Room \n The Office \n The Armory \n Guest Bedroom\n\n");
    printf("List of characters: \n Makima \n Drew \n Kevin \n Panda \n Giuseppe \n Steven\n\n");
    printf("List of items: \n sword \n controller \n hammer \n finger \n sculpture \n arrow\n\n");
}

void inventory(struct Avatar* user) {
    //check if inventory is empty
    if (user->inventory->next == NULL) {
        printf("Your inventory is currently empty\n");
        return;
    }
    //iterates through inventory and prints each non dummy item
    struct Item* cur = item("cur", "cur", user->inventory);
    printf("In your inventory, you have: \n");
    cur = cur->next;
    while(cur->next != NULL) {
        printf("%s\n", cur->next->name);
        cur = cur->next;
    }
}

void move_avatar(struct Avatar* user, char* direction) {
    //checks each direction and changes pointers accordingly
    if (strcmp(direction, "n") == 0) {
        if (user->curRoom->north == NULL) {
            printf("You walked into a wall, choose a different direction\n");
        } else {
            user->curRoom = user->curRoom->north;
        }
    } else if (strcmp(direction, "s") == 0) {
        if (user->curRoom->south == NULL) {
            printf("You walked into a wall, choose a different direction\n");
        } else {
            user->curRoom = user->curRoom->south;
        }
    } else if (strcmp(direction, "e") == 0) {
        if (user->curRoom->east == NULL) {
            printf("You walked into a wall, choose a different direction\n");
        } else {
            user->curRoom = user->curRoom->east;
        }
    } else if (strcmp(direction, "w") == 0) {
        if (user->curRoom->west == NULL) {
            printf("You walked into a wall, choose a different direction\n");
        } else {
            user->curRoom = user->curRoom->west;
        }
    }
}

int clue(struct Avatar* user, struct Character* person, struct Murder* killing) {
    //if the user corrects the correct one of these, their value becomes 1 and if the sum of them is 3 at the end, then player wins
    int rightRoom = 0;
    int rightItem = 0;
    int rightPerson = 0;
    //check if player got the room correct
    printf("Investigating the room....\n");
    int roomChk = strcmp(user->curRoom->description, killing->room->description);
    if (roomChk == 0) {
        printf("Room Match\n");
        rightRoom = 1;
    }
    //check if player got the item correct
    printf("Investigating the item....\n");
    //checks inventory first, then checks the rest of the room for items if it wasn't in the inventory
    struct Item* invPtr = item("ptr", "ptr", user->inventory);
    while (invPtr->next != NULL) {
        int itemChk = strcmp(invPtr->next->name, killing->item->name);
        if (itemChk == 0) {
            printf("Item Match\n");
            rightItem = 1;
            break;
        }
        invPtr = invPtr->next;
    }
    if (rightItem == 0) {
        struct Item* stuff = item("ptr", "ptr", user->curRoom->items);
        while (stuff->next != NULL) {
            int itemChk2 = strcmp(stuff->next->name, killing->item->name);
            if (itemChk2 == 0) {
                printf("Item Match\n");
                rightItem = 1;
                break;
            }
            stuff = stuff->next;
        }
    }
    //checks is player got the person correct
    printf("Investigating the person....\n");
    int init = strcmp(user->curRoom->description, person->in->description);
    if (init != 0) {
        move_character(user->curRoom, person);
    }
    if (strcmp(person->name, killing->person->name) == 0) {
        printf("Character Match\n");
        rightPerson = 1;
    } 
    guessCounter++;
    if (rightPerson + rightItem + rightRoom == 3) {
        return 1;
    } else if (rightPerson + rightItem + rightRoom == 0) {
        printf("no matches\n");
    }
    return 0;
}



int main() {
    //Initializing all the pieces of the game to start
    time_t t;
    int win = 0;
    srand((unsigned)time(&t));
    struct Item* roomDummyItems1 = item("dummy", "dummy for items", NULL);
    struct Character* roomDummyChar1 = npc("dummy", "dummy for characters", NULL, NULL);
    struct Room* room1 = room(NULL, NULL, NULL, NULL, roomDummyItems1, roomDummyChar1, "Unnamed");
    struct Item* roomDummyItems2 = item("dummy", "dummy for items", NULL);
    struct Character* roomDummyChar2 = npc("dummy", "dummy for characters", NULL, NULL);
    struct Room* room2 = room(NULL, NULL, NULL, NULL, roomDummyItems2, roomDummyChar2, "Unnamed");
    struct Item* roomDummyItems3 = item("dummy", "dummy for items", NULL);
    struct Character* roomDummyChar3 = npc("dummy", "dummy for characters", NULL, NULL);
    struct Room* room3 = room(NULL, NULL, NULL, NULL, roomDummyItems3, roomDummyChar3, "Unnamed");
    struct Item* roomDummyItems4 = item("dummy", "dummy for items", NULL);
    struct Character* roomDummyChar4 = npc("dummy", "dummy for characters", NULL, NULL);
    struct Room* room4 = room(NULL, NULL, NULL, NULL, roomDummyItems4, roomDummyChar4, "Unnamed");
    struct Item* roomDummyItems5 = item("dummy", "dummy for items", NULL);
    struct Character* roomDummyChar5 = npc("dummy", "dummy for characters", NULL, NULL);
    struct Room* room5 = room(NULL, NULL, NULL, NULL, roomDummyItems5, roomDummyChar5, "Unnamed");
    struct Item* roomDummyItems6 = item("dummy", "dummy for items", NULL);
    struct Character* roomDummyChar6 = npc("dummy", "dummy for characters", NULL, NULL);
    struct Room* room6 = room(NULL, NULL, NULL, NULL, roomDummyItems6, roomDummyChar6, "Unnamed");
    struct Item* roomDummyItems7 = item("dummy", "dummy for items", NULL);
    struct Character* roomDummyChar7 = npc("dummy", "dummy for characters", NULL, NULL);
    struct Room* room7 = room(NULL, NULL, NULL, NULL, roomDummyItems7, roomDummyChar7, "Unnamed");
    struct Item* roomDummyItems8 = item("dummy", "dummy for items", NULL);
    struct Character* roomDummyChar8 = npc("dummy", "dummy for characters", NULL, NULL);
    struct Room* room8 = room(NULL, NULL, NULL, NULL, roomDummyItems8, roomDummyChar8, "Unnamed");
    struct Item* roomDummyItems9 = item("dummy", "dummy for items", NULL);
    struct Character* roomDummyChar9 = npc("dummy", "dummy for characters", NULL, NULL);
    struct Room* room9 = room(NULL, NULL, NULL, NULL, roomDummyItems9, roomDummyChar9, "Unnamed");
    struct Item* item1 = item("sword", "a double-edged longsword", NULL);
    struct Item* item2 = item("controller", "Looks broken", NULL);
    struct Item* item3 = item("finger", "A severed finger wrapped in cloth with weird writing", NULL);
    struct Item* item4 = item("hammer", "A light blue aura emanating from it", NULL);
    struct Item* item5 = item("sculpture", "Made out of red wax", NULL);
    struct Item* item6 = item("arrow", "The front half of a golden tipped arrow", NULL);
    struct Character* char1 = npc("Makima", "A friendly ginger lady", NULL, NULL);
    struct Character* char2 = npc("Drew", "Looks like he's never left the gaming room in his life", NULL, NULL);
    struct Character* char3 = npc("Panda", "A walking talking panda??", NULL, NULL);
    struct Character* char4 = npc("Giuseppe", "An angry italian pilot", NULL, NULL);
    struct Character* char5 = npc("Steven", "Very disturbing blank face", NULL, NULL);
    struct Character* char6 = npc("Kevin", "a massive lizard that can communicate telepathically", NULL, NULL);
    struct Item* playerDummy = item("dummy", "dummy", NULL);
    struct Avatar* user = player(playerDummy, room1);
    char* names[9] = {"The Kitchen", "The Master Bedroom", "The Bathroom", "The Indoor Pool", "The Planetarium", "The Gaming Room",
    "The Office", "The Armory", "The Guest Bedroom"};
    struct Room* rooms[9] = {room1, room2, room3, room4, room5, room6, room7, room8, room9};
    struct Character* people[6] = {char1, char2, char3, char4, char5, char6};
    struct Item* items[6] = {item1, item2, item3, item4, item5, item6};
    //Randomizing rooms
    for (int i = 0; i < 9; i++) {
        int roomFound = 0;
        while (roomFound == 0) {
            int spot = rand() % 9;
            int ans = strcmp(rooms[spot]->description, "Unnamed");
            if (ans == 0) {
                rooms[spot]->description = names[i];
                roomFound = 1;
            }
        }
    }
    //Randomizing items
    for (int i = 0; i < 6; i++) {
        int roomFound = 0;
        while (roomFound == 0) {
            int spot = rand() % 9;
            if (rooms[spot]->items->next == NULL) {
                roomFound = 1;
                rooms[spot]->items->next = items[i];
            }
        } 
    }
    //Randomizing characters
    for (int i = 0; i < 6; i++) {
        int roomFound = 0;
        while (roomFound == 0) {
            int spot = rand() % 9;
            if (rooms[spot]->people->others == NULL) {
                roomFound = 1;
                rooms[spot]->people->others = people[i];
                people[i]->in = rooms[spot];
            }
        } 
    }
    //Randomizing the murder
    int murderer = rand() % 6;
    int murderItem = rand() % 6;
    int murderRoom = rand() % 9;
    struct Murder* killing = murder(rooms[murderRoom], items[murderItem], people[murderer]);
    //linking rooms to form 3x3 grid
    room1->north = room4;
    room1->south = room6;
    room1->east = room7;
    room1->west = room3;
    room2->south = room7;
    room2->west = room4;
    room3->north = room5;
    room3->south = room9;
    room3->east = room1;
    room4->south = room1;
    room4->west = room5;
    room4->east = room2;
    room5->south = room3;
    room5->east = room4;
    room6->north = room1;
    room6->west = room9;
    room6->east = room8;
    room7->north = room2;
    room7->south = room8;
    room7->west = room1;
    room8->north = room7;
    room8->west = room6;
    room9->north = room3;
    room9->east = room6;
    //this is where the game runs
    while(guessCounter < 10){
        printf("You are in %s\n\n", user->curRoom->description);
        printf("What are you going to do?\n");
        //gets the user input with this
        char *str;
        size_t size = 100;
        str = (char*) malloc(size * sizeof(char));
        int character = getline(&str, &size, stdin);
        if (character != -1) {
            printf("\n");
        }
        //gets first word of input and compares it to every command word to find the match
        char *token = strtok(str, " \n");
        if (strcmp(token, "look") == 0) {
            look(user->curRoom);
        } else if (strcmp(token, "help") == 0) {
            help();
        } else if (strcmp(token, "list") == 0) {
            list();
        } else if (strcmp(token, "go") == 0) {
            //gets second word and compares it to every direction to find match
            token = strtok(NULL, " \n");
            if (strcmp(token, "north") == 0) {
                move_avatar(user, "n");
            } else if (strcmp(token, "south") == 0) {
                move_avatar(user, "s");
            } else if (strcmp(token, "east") == 0) {
                move_avatar(user, "e");
            } else if (strcmp(token, "west") == 0) {
                move_avatar(user, "w");
            } else {
                printf("that is not a valid direction\n");
            }
        } else if (strcmp(token, "inventory") == 0) {
            inventory(user);
        } else if(strcmp(token, "take") == 0) {
            token = strtok(NULL, " \n");
            if (strcmp(token, "sword") == 0) {
                add_item(user, "sword");
            } else if (strcmp(token, "hammer") == 0) {
                add_item(user, "hammer");
            } else if (strcmp(token, "controller") == 0) {
                add_item(user, "controller");
            } else if (strcmp(token, "finger") == 0) {
                add_item(user, "finger");
            } else if (strcmp(token, "sculpture") == 0) {
                add_item(user, "sculpture");
            } else if (strcmp(token, "arrow") == 0) {
                add_item(user, "arrow");
            } else {
                printf("That item does not exist\n");
            }
        } else if(strcmp(token, "drop") == 0) {
            token = strtok(NULL, " \n");
            if (strcmp(token, "sword") == 0) {
                drop_item(user, "sword");
            } else if (strcmp(token, "hammer") == 0) {
                drop_item(user, "hammer");
            } else if (strcmp(token, "controller") == 0) {
                drop_item(user, "controller");
            } else if (strcmp(token, "finger") == 0) {
                drop_item(user, "finger");
            } else if (strcmp(token, "sculpture") == 0) {
                drop_item(user, "sculpture");
            } else if (strcmp(token, "arrow") == 0) {
                drop_item(user, "arrow");
            } else {
                printf("That item does not exist\n");
            }
        } else if(strcmp(token, "clue") == 0) {
            token = strtok(NULL, " \n");
            int correct = 0;
            if (strcmp(token, "Makima") == 0) {
                correct = clue(user, char1, killing);
                if (correct == 1) {
                    win = 1;
                } else {
                    printf("you have %i guesses left\n", 10-guessCounter);
                }
            } else if (strcmp(token, "Drew") == 0) {
                correct = clue(user, char2, killing);
                if (correct == 1) {
                    win = 1;
                } else {
                    printf("you have %i guesses left\n", 10-guessCounter);
                }
            } else if (strcmp(token, "Panda") == 0) {
                correct = clue(user, char3, killing);
                if (correct == 1) {
                    win = 1;
                } else {
                    printf("you have %i guesses left\n", 10-guessCounter);
                }
            } else if (strcmp(token, "Giuseppe") == 0) {
                correct = clue(user, char4, killing);
                if (correct == 1) {
                    win = 1;
                } else {
                    printf("you have %i guesses left\n", 10-guessCounter);
                }
            } else if (strcmp(token, "Steven") == 0) {
                correct = clue(user, char5, killing);
                if (correct == 1) {
                    win = 1;
                } else {
                    printf("you have %i guesses left\n", 10-guessCounter);
                }
            } else if (strcmp(token, "Kevin") == 0) {
                correct = clue(user, char6, killing);
                if (correct == 1) {
                    win = 1;
                } else {
                    printf("you have %i guesses left\n", 10-guessCounter);
                }  
            } else {
                printf("That is not a character\n");
            }
        } else {
            printf("That is not a valid command\n");
        }
        //goes here if character gets all 3 matches
        if (win == 1) {
            printf("Congratulations! You solved the mystery\n It was %s in %s using the %s\n", killing->person->name,
            killing->room->description, killing->item->name);
            free(str);
            break;
        }
        //goes here if player doesn't get 3 matches in 10 guesses
        if (guessCounter >= 10) {
            printf("You lose!\n It was %s in %s using the %s\n", killing->person->name,
            killing->room->description, killing->item->name);
        }
        //freeing everything because apparently we have to do this
        free(str);
        
    }
    free(roomDummyChar1);
    free(roomDummyChar2);
    free(roomDummyChar3);
    free(roomDummyChar4);
    free(roomDummyChar5);
    free(roomDummyChar6);
    free(roomDummyChar7);
    free(roomDummyChar8);
    free(roomDummyChar9);
    free(roomDummyItems1);
    free(roomDummyItems2);
    free(roomDummyItems3);
    free(roomDummyItems4);
    free(roomDummyItems5);
    free(roomDummyItems6);
    free(roomDummyItems7);
    free(roomDummyItems8);
    free(roomDummyItems9);
    free(item1);
    free(item2);
    free(item3);
    free(item4);
    free(item5);
    free(item6);
    free(char1);
    free(char2);
    free(char3);
    free(char4);
    free(char5);
    free(char6);
    free(user);
    free(playerDummy);
    return 1;
}