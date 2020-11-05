#include "character.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Character* npc(char *name, char *description, struct Character *others, struct Room *in){
    struct Character *person = (struct Character*) malloc(sizeof(struct Character));
    if (person == NULL) {
        return NULL;
    }
    person->name = name;
    person->description = description;
    person->others = others;
    person->in = in;
    return person;
}

struct Avatar* player(struct Item *inventory, struct Room *curRoom) {
    struct Avatar *person = (struct Avatar*) malloc(sizeof(struct Avatar));
    if (person == NULL) {
        return NULL;
    }
    person->inventory = inventory;
    person->curRoom = curRoom;
    return person;
}

void move_character(struct Room *room, struct Character *person) {
    struct Character *cur = npc("ptr", "cur", person->in->people, person->in);
    //finds the location of the person in the given pointer of their room
    while(cur->others != NULL) {
        int ans = strcmp(cur->others->name, person->name);
        if (ans == 0) {
            struct Character* ptr = room->people;
            //pointer to the end of room people list
            while (ptr->others != NULL) {
                ptr = ptr->others;
            }
            struct Character* temp = npc("target", "target", cur->others, NULL);
            //ensuring we only move the target person 
            cur->others = cur->others->others;
            temp->others->others = NULL;
            temp->others->in = room;
            ptr->others = temp->others;
            break;
        }
        cur = cur->others;
    }
}
