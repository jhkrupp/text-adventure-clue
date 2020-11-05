#include "items.h"
#include "room.h"
#include "character.h"
#include<stdio.h>
#include<string.h>

struct Item* item(char* name, char* description, struct Item *next) {
  struct Item *newItem = (struct Item*) malloc(sizeof(struct Item));
  if (newItem == NULL) {
    return NULL;
  }
  newItem->name = name;
  newItem->description = description;
  newItem->next = next;
  return newItem;
}

void add_item(struct Avatar* user, char* name) {
    struct Item* cur = item("cur", "cur", user->curRoom->items);
    //searches for the item name in the room
    while (cur->next != NULL) {
        int ans = strcmp(cur->next->name, name);
        if (ans == 0) {
            printf("picked up %s\n", name);
            struct Item* ptr = item("ptr", "ptr,", user->inventory);
            //gets a pointer to the end of the user inventory
            while(ptr->next != NULL) {
                ptr = ptr->next;
            }
            struct Item* temp = item("target", "target", cur->next);
            //making sure we only take that item and not the ones linked after it
            cur->next = cur->next->next;
            temp->next->next = NULL;
            ptr->next = temp->next;
            return;
        }
        cur = cur->next;
    }
    printf("that item is not in this room...\n");
}

void drop_item(struct Avatar* user, char* name) {
    struct Item* cur = item("cur", "cur", user->inventory);
    //checks to find item in the room
    while (cur->next != NULL) {
        int ans = strcmp(cur->next->name, name);
        if (ans == 0) {
            struct Item* ptr = item("cur", "cur", user->curRoom->items);
            //gets a pointer to the end of user inventory
            while (ptr->next != NULL) {
                   ptr = ptr->next;
            }
            struct Item* temp = item("target", "target", cur->next);
            //making sure we only drop the item we want to drop
            cur->next = cur->next->next;
            temp->next->next = NULL;
            ptr->next = temp->next;
            printf("dropped %s\n", name);
            return;
        }
        cur = cur->next;
    }
    printf("you cannot drop an item you are not carrying\n");    
}