#include<stdlib.h>
#ifndef ITEMS_H
#define ITEMS_H
#include "character.h"
struct Item {
   char *name;
   char *description;
   struct Item *next;
};

struct Item* item(char* name, char* description, struct Item *next);
void add_item(struct Avatar *user, char *item);
void drop_item(struct Avatar *user, char *item);
#endif