
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "LinkedList.h"


// **** Declare any function prototypes here ***
ListItem *CreateUnsortedList(void); //this function has been written for you
ListItem *SelectionSort(ListItem* list);
ListItem *InsertionSort(ListItem* list);


/* Students should not need to modify main! */
int main(void)
{
    BOARD_Init();

    printf("\n\nWelcome to saegomez's sort.c, compiled on %s %s.\n", __DATE__, __TIME__);

    ListItem* listToSort;

    //Do a timing test 
    printf("\nStarting stopwatch for selection sort...\n");
    listToSort = CreateUnsortedList();
    __asm("nop"); //put a breakpoint on this line
    listToSort = SelectionSort(listToSort);
    __asm("nop"); //put a breakpoint on this line, and record the stopwatch time
    LinkedListPrint(listToSort);


    printf("\nStarting stopwatch for insertion sort...\n");
    listToSort = CreateUnsortedList();
    __asm("nop"); //put a breakpoint on this line
    listToSort = InsertionSort(listToSort);
    __asm("nop"); //put a breakpoint on this line, and record the stopwatch time
    LinkedListPrint(listToSort);

    BOARD_End();
    while (1);
    return 0;
}

/**
 * SelectionSort() performs a selection sort on a passed to it.  The list is sorted alphabetically,
 * as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member.  It also assumes that 'list'
 * is a valid, non-NULL pointer to a linked list.
 * 
 * This function does not print.
 */
ListItem *SelectionSort(ListItem* list) {
    if (!list) return NULL; // Return Null if the list is empty

    ListItem *start = list, *min, *current;
    char *tempData;

    // Iterate over each element in the list except the last one 
    while (start->nextItem) {
        min = start; // Assumes the first element in list is the minimum
        current = start->nextItem; // Start checking from the second element

        while (current) {
            if (strcmp(current->data, min->data) < 0) {
                min = current; // Update minimum if a smaller element is found
            }
            current = current->nextItem; // Move to the next element
        }
        // Swap the data of start and min if they do not match
        if (min != start) {
            tempData = start->data;
            start->data = min->data;
            min->data = tempData;
        }
        start = start->nextItem; // Move to the next element and repeat
    }
    return list; 
}



/**
 * InsertionSort() performs an insertion sort on a passed to it.  The list is sorted alphabetically,
 * as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member.  It also assumes that 'list'
 * is a valid, non-NULL pointer to a linked list.
 * 
 * This function does not print.
 */
ListItem *InsertionSort(ListItem *list) {
    if (!list) return NULL; 

    ListItem *sorted = NULL, *current = list, *next, *prev;
    
    // Iterate over each element in the original list
    while (current) {
        next = current->nextItem; // Store the next item to process later
        
        // Find the correct position and insert the current item in sorted list
        if (!sorted || strcmp(sorted->data, current->data) >= 0) {
            // Insert before the first element of the sorted list
            current->nextItem = sorted;
            if (sorted) {
                sorted->previousItem = current;
            }
            current->previousItem = NULL;
            sorted = current; // Updating the head of the sorted list
        } else {
            // Insert after the first element of the sorted list
            prev = sorted;
            // Finding the proper place for insertion
            while (prev->nextItem && strcmp(prev->nextItem->data, current->data) < 0) {
                prev = prev->nextItem; // Continue until a larger element is found
            }
            // Insert current between prev and prev's next
            current->nextItem = prev->nextItem;
            if (prev->nextItem) {
                prev->nextItem->previousItem = current;
            }
            prev->nextItem = current;
            current->previousItem = prev; 
        }

        current = next; 
    }
    return sorted; 
}


/* CreateUnsortedList() uses the functions in the LinkedList library to
 * generate an unsorted list.  
 * 
 * Students should not modify this function!
 * If an error occurs in this function, there is almost certainly 
 * a bug in your implementation of LinkedList.h.
 *   
 * @return A pointer to a ListItem which is the head of a new unsorted list. 
 */
ListItem *CreateUnsortedList(void)
/// <editor-fold defaultstate="collapsed" desc="CreateUnsortedList definition">
{
 char* wordList[] = {
        "decide",   "toothpaste",   "lowly",        "robin",        "reign",        "crowd",
        "pies",     "reduce",       "tendency",     "surround",     "finger",       "rake", 
        "alleged",  "hug",          "nest",         "punishment",   "eggnog",       "side", 
        "beef",     "exuberant",    "sort",         "scream",       "zip",          "hair", 
        "ragged",   "damage",       "thought",      "jump",         "frequent",     "substance",
        "head",     "step",         "faithful",     "sidewalk",     "pig",          "raspy",
        "juggle",   "shut",         "maddening",    "rock",         "telephone",    "selective",
        NULL};
    //  char* wordList[] = {"D", "A", "C", "E", "B", NULL};


    int i = 0;
    ListItem* head = LinkedListNew(wordList[i]);
    ListItem* tail = head;
    for (i = 1; wordList[i] != NULL; i++) {
        tail = LinkedListCreateAfter(tail, wordList[i]);
        if(tail == NULL){
            printf("ERROR:  Heap full! Please increase heap size.\n");
            FATAL_ERROR();
        }
    }
    return head;
}
// </editor-fold>
