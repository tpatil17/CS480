# CS480
Assignment 1

The assignment implements tree data structure to emulate Paging done by computers to store addresses and reccord page numbers

The main.c file take a file input which contains the addresses that need to be traversed and returns a log of the page numbers, and the number of time a page was accessed.

Innitially the program only boots a page table structure that stores information about the susequent tree, it has a pointer that points to a Page Level structure which initially contains an array of pointers

The array of pointers will in future point to other page levels, page levels are created as the main address is traversed, if a page alredy exists it is not recreated. 


