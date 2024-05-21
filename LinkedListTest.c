// Saul Gomez ECE13 Lab 05 LinkedListTest.c
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include <string.h>

// Function prototypes for test functions
void testLinkedListNew();
void testLinkedListCreateAfter();
void testLinkedListRemove();
void testLinkedListSize();
void testLinkedListGetFirst();
void testLinkedListGetLast();
void testLinkedListSwapData();
void testLinkedListPrint();

int main() {
    testLinkedListNew();
    testLinkedListCreateAfter();
    testLinkedListRemove();
    testLinkedListSize();
    testLinkedListGetFirst();
    testLinkedListGetLast();
    testLinkedListSwapData();
    testLinkedListPrint();
    return 0;
}

// Test creation of new list items
void testLinkedListNew() {
    printf("Testing LinkedListNew...\n");
    ListItem *item1 = LinkedListNew("First item");
    ListItem *item2 = LinkedListNew(NULL); // Testing with NULL to ensure function handles it
    printf("Test 1: Expected non-NULL, Actual: %p\n", (void*)item1);
    printf("Test 2: Expected non-NULL, Actual: %p\n", (void*)item2);

    // Cleanup: Ensure memory is freed properly
    LinkedListRemove(item1);
    LinkedListRemove(item2);
}

// Test insertion after a given item
void testLinkedListCreateAfter() {
    printf("Testing LinkedListCreateAfter...\n");
    ListItem *item1 = LinkedListNew("First item");
    ListItem *item2 = LinkedListCreateAfter(item1, "Second item");
    ListItem *item3 = LinkedListCreateAfter(NULL, "Third item"); // Test insert on NULL
    printf("Test 1: Expected non-NULL, Actual: %p\n", (void*)item2);
    printf("Test 2: Expected non-NULL, Actual: %p\n", (void*)item3);

    // Cleanup
    LinkedListRemove(item1);
    LinkedListRemove(item2);
    LinkedListRemove(item3);
}

// Test removal of items
void testLinkedListRemove() {
    printf("Testing LinkedListRemove...\n");
    char *removableData = strdup("Item to remove");
    ListItem *item1 = LinkedListNew(removableData);

    char *data = LinkedListRemove(item1);
    printf("Test 1: Expected data 'Item to remove', Actual: %s\n", data);
    free(data); // Free the data obtained from removal

    // Test removal safety on NULL
    data = LinkedListRemove(NULL);
    printf("Test 2: Expected NULL, Actual: %p\n", (void*)data);
}

// Test getting the size of the list
void testLinkedListSize() {
    printf("Testing LinkedListSize...\n");
    ListItem *item1 = LinkedListNew("First item");
    ListItem *item2 = LinkedListCreateAfter(item1, "Second item");
    int size1 = LinkedListSize(item1);
    printf("Test 1: Expected size 2, Actual: %d\n", size1);
    printf("Test 2: Expected size 0, Actual: %d\n", LinkedListSize(NULL));

    // Cleanup
    LinkedListRemove(item1);
    LinkedListRemove(item2);
}

// Test getting the first item in the list
void testLinkedListGetFirst() {
    printf("Testing LinkedListGetFirst...\n");
    ListItem *item1 = LinkedListNew("First item");
    ListItem *item2 = LinkedListCreateAfter(item1, "Second item");
    ListItem *firstItem = LinkedListGetFirst(item2);
    printf("Test 1: Expected same as item1, Actual: %p\n", (void*)firstItem);
    printf("Test 2: Expected NULL, Actual: %p\n", (void*)LinkedListGetFirst(NULL));

    // Cleanup
    LinkedListRemove(item1);
    LinkedListRemove(item2);
}

// Test getting the last item in the list
void testLinkedListGetLast() {
    printf("Testing LinkedListGetLast...\n");
    ListItem *item1 = LinkedListNew("First item");
    ListItem *item2 = LinkedListCreateAfter(item1, "Second item");
    ListItem *lastItem = LinkedListGetLast(item1);
    printf("Test 1: Expected same as item2, Actual: %p\n", (void*)lastItem);
    printf("Test 2: Expected NULL, Actual: %p\n", (void*)LinkedListGetLast(NULL));

    // Cleanup
    LinkedListRemove(item1);
    LinkedListRemove(item2);
}

// Test swapping data between two items
void testLinkedListSwapData() {
    printf("Testing LinkedListSwapData...\n");
    ListItem *item1 = LinkedListNew("First item");
    ListItem *item2 = LinkedListCreateAfter(item1, "Second item");
    int result1 = LinkedListSwapData(item1, item2);
    printf("Test 1: Expected SUCCESS, Actual: %d\n", result1);
    printf("Test 2: Expected STANDARD_ERROR, Actual: %d\n", LinkedListSwapData(item1, NULL));

    // Cleanup
    LinkedListRemove(item1);
    LinkedListRemove(item2);
}

// Test printing the list
void testLinkedListPrint() {
    printf("Testing LinkedListPrint...\n");
    ListItem *item1 = LinkedListNew("First item");
    ListItem *item2 = LinkedListCreateAfter(item1, "Second item");
    LinkedListPrint(item1);
    LinkedListPrint(NULL); // Test print functionality with NULL

    // Cleanup
    LinkedListRemove(item1);
    LinkedListRemove(item2);
}