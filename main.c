//************************************************************************
// Name: Tanishq Patil
// RED ID: 132639686
// Class: CS 480
// Assignment 1
//************************************************************************
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "PageTableLevel.h"
#include "tracereader.h"
#include "log.h"
#include "BitMasker.h"
#include<math.h>


int main(int argc, char* argv[]){
    
    // Check for input validity and fail gracefully if incorrect
    if(argv[2] == NULL){
        perror("incomplete parameters\n");
        exit(1);
    }

    FILE* addrFile; // File pointer to read in the file
    p2AddrTr mTrace; // the address ptr that stores adress read from file

    unsigned int vAddr; // will store the newly read addr

    addrFile = fopen(argv[1], "r");
    // verify if the file opened correctly
    if(addrFile == NULL){
        perror("Unable to open <<trace.tr>>\n");
        exit(1);
    }

    // Get in the structure specifics
    
    int lvls = NumLvl(argv[2]); // number of levels

    int* treeScheme = processString(argv[2], lvls); // array of bit counts per level

    // Base on the given scheme calculate masks and shift sizes for each level
    unsigned int* masks = GenerateMask(lvls, treeScheme);
    unsigned int* shiftSizes = GetShiftSizes(treeScheme, lvls);
    unsigned int* ptrArraySizes = (unsigned int*)malloc(sizeof(unsigned int)*lvls); // the array size for each page level

    if(ptrArraySizes == NULL){
        perror("Memory allocation failed\n");
    }
    // Explicit declaration of ptrArray
    for(int i = 0; i < lvls; i++){
        ptrArraySizes[i] = 0;
    }
    // Get the entry count size for each level
    for(int i = 0; i < lvls; i++){
        // 1 << x, where x is an intiger value, resluts in 1*(2^x)
        // Hence in our case 1 << (number of bits assigned for a level) will yield 2^bits or the size of nextPtrarray
        ptrArraySizes[i] = 1 << treeScheme[i]; 

    }

    // Start the Page Table
    PageTable Root = startPageTable(lvls); 

    // Initialize all table values
    Root.bitMasks = masks;
    Root.shift_array = shiftSizes;
    Root.entryCount = ptrArraySizes;

    //log all the table details
    log_bitmasks(lvls, Root.bitMasks);

    //Initialize Page level 0

    PageLevel lvl0 = startPageLevel(0, &Root, ptrArraySizes[0]); // start with level zero

    Root.zeroPage = &lvl0; // Zero page is a pointer inside Page table that points at level 0
    // All pointers at level 00 are set to null
    
    // The Program initializes 

    // read in the next address
    while(NextAddress(addrFile, &mTrace)){

        vAddr = mTrace.addr; // the address to be processed
        // Line below calculates all the page indices for each level and stores it in an array, where array index corresponds to level
        unsigned int* PageIndiceArr = pageIndice(Root.bitMasks, Root.shift_array, vAddr, Root.levelCount);
        //Count the number of time an address was visited
        unsigned int accessCount = recordPageAccess(vAddr, &lvl0);
        //log the access info
        log_pgindices_numofaccesses(vAddr, lvls, PageIndiceArr, accessCount);

    }
    


    return 1;
}
