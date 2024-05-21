// Saul Gomez ECE13 Lab05 LinkedList.c
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

// Definition of SUCCESS and STANDARD_ERROR for clarity in the code
#define SUCCESS 1
#define STANDARD_ERROR 0

// Creates a new linked list item with provided data and initializes pointers
ListItem* LinkedListNew(char *data) {
    // Allocate memory for a new list item
    ListItem* newItem = (ListItem*)malloc(sizeof(ListItem));
    if (newItem == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }
    newItem->data = data; // Set the data pointer
    newItem->previousItem = NULL; // No previous item as this is the first item
    newItem->nextItem = NULL; // No next item as this is the only item
    return newItem;
}

// Inserts a new item after the specified item in the list
ListItem* LinkedListCreateAfter(ListItem *item, char *data) {
    // Allocate memory for the new list item
    ListItem* newItem = (ListItem*)malloc(sizeof(ListItem));
    if (newItem == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }
    newItem->data = data; // Set the data for the new item
    newItem->nextItem = (item ? item->nextItem : NULL); // Link new item's next to item's next
    newItem->previousItem = item; // Set the previous to the item

    if (item) {
        if (item->nextItem) {
            item->nextItem->previousItem = newItem; // Link back from the old next item to new item
        }
        item->nextItem = newItem; // Place new item right after the existing item
    }
    return newItem;
}

// Removes an item from the list and returns the data pointer
char* LinkedListRemove(ListItem *item) {
    if (item == NULL) {
        return NULL; // Early exit if the item is NULL
    }
    // Disconnect the node from its neighbors
    if (item->previousItem) {
        item->previousItem->nextItem = item->nextItem;
    }
    if (item->nextItem) {
        item->nextItem->previousItem = item->previousItem;
    }
    char* data = item->data;
    free(item); // Free the ListItem struct itself
    return data; // Return the data pointer, which must be managed or freed outside this function
}


// Returns the size of the list by counting all items
int LinkedListSize(ListItem *list) {
    int count = 0;
    ListItem* current = LinkedListGetFirst(list); // Start at the first item
    while (current != NULL) {
        count++; // Increment counter for each item
        current = current->nextItem; // Move to the next item
    }
    return count;
}

// Returns a pointer to the first item in the list
ListItem* LinkedListGetFirst(ListItem *list) {
    if (list == NULL) {
        return NULL; // Return NULL if the list is empty
    }
    while (list->previousItem != NULL) {
        list = list->previousItem; // Traverse back to the first item
    }
    return list;
}

// Returns a pointer to the last item in the list
ListItem* LinkedListGetLast(ListItem *list) {
    if (list == NULL) {
        return NULL; // Return NULL if the list is empty
    }
    while (list->nextItem != NULL) {
        list = list->nextItem; // Traverse forward to the last item
    }
    return list;
}

// Swaps the data pointers of two list items
int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem) {
    if (firstItem == NULL || secondItem == NULL) {
        return STANDARD_ERROR; // Return error if any item is NULL
    }
    char* temp = firstItem->data; // Temporary storage for first item's data
    firstItem->data = secondItem->data; // Swap data
    secondItem->data = temp; // Complete the swap
    return SUCCESS; // Return success after swap
}

// Prints the complete list starting from the head
int LinkedListPrint(ListItem *list) {
    if (list == NULL) {
        return STANDARD_ERROR; // Do nothing if the list is NULL
    }
    list = LinkedListGetFirst(list); // Start at the head of the list
    printf("[");
    while (list != NULL) {
        printf("%s", list->data ? list->data : "NULL"); // Print the data of each item
        if (list->nextItem != NULL) {
            printf(", "); // Add comma between items
        }
        list = list->nextItem; // Move to the next item
    }
    printf("]\n");
    return SUCCESS; // Return success after printing
}

