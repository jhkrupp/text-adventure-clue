#include "room.h"
struct Room* room(struct Room *north, struct Room *south, struct Room *east, struct Room *west, struct Item *items, struct Character *people, char *name) {
    struct Room *newRoom = (struct Room*) malloc(sizeof(struct Room));
    if (newRoom == NULL) {
        return NULL;
    }
    newRoom->north = north;
    newRoom->south = south;
    newRoom->east = east;
    newRoom->west = west;
    newRoom->description = name;
    newRoom->items = items; 
    newRoom->people = people;
    return newRoom;
}