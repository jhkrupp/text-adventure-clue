#include<stdlib.h>
#ifndef CHARACTER_H
#define CHARACTER_H
#include "room.h"
struct Character {
    char *name;
    char *description;
    struct Character *others;
    struct Room *in;
};
struct Avatar {
    struct Item *inventory;
    struct Room *curRoom;
};

struct Avatar* player(struct Item *inventory, struct Room *curRoom);
struct Character* npc(char *name, char *description, struct Character *other, struct Room *in);
void move_character(struct Room *room, struct Character *person);
#endif