#include<stdlib.h>
#ifndef ROOM_H
#define ROOM_H
struct Room {
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
    struct Item *items;
    char *description;
    struct Character *people;
};

struct Room* room(struct Room *north, struct Room *south, struct Room *East, struct Room *west, struct Item *items, struct Character *people, char *description);
#endif