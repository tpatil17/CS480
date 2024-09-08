//************************************************************************
// Name: Tanishq Patil
// RED ID: 132639686
// Class: CS 480
// Assignment 1
//************************************************************************
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "BitMasker.h"


// Function to generate an array of masks give the tree scheme
//
unsigned int* GenerateMask(int lvls, int* arr){
    // for a 32 bit long address size, as is the standard for this assignment
    unsigned int base = 0xFFFFFFFF; // if all 32 bits were 1, its hex representation is 8 F's
    int carry = 0;
    unsigned int* maskArray = (unsigned int*)malloc(sizeof(unsigned int)*lvls);

    for(int i = 0; i < lvls; i++){
        maskArray[i] = 0;
    }


    for(int i = 0; i < lvls; i++){
        int pgSize = arr[i]; // the bits for the current level
        unsigned int mask = base >> carry; // to adjust for the front bits
        
        int shiftSize = 32 - (carry+pgSize); // 32 here is the number of bits in an address
       
        mask = mask >> shiftSize;
        mask = mask << shiftSize;
 
        maskArray[i] = mask;
        carry = carry+pgSize;
        
    }

    return maskArray;

}


// Calculates the shiftsize for each level

unsigned int* GetShiftSizes(int* arr, int lvls){
    unsigned int* shiftArray = (unsigned int*)malloc(sizeof(unsigned int)*lvls);
    //explicit declaration
    for(int i = 0; i < lvls; i++){
        shiftArray[i] = 0;
    }
 

    // Function Logic
    int carry = 0;

    for(int i = 0; i < lvls; i++){
        
        shiftArray[i] = 32 - (arr[i]+carry); // 32 is the number of bits in an address
        carry = carry + arr[i];
    }

    return shiftArray;

}

// process the string input to convert it into an array of ints
int* processString(char* arr, int lvls){
    

    int* retArr = (int*)malloc(sizeof(int)*lvls);
    //Explicit declaration
    for(int i = 0; i < lvls; i++){
        retArr[i] = 0;
    }
    int i = 0;
    int j = 0;
    while(arr[i] && j < lvls){
        retArr[j] = atoi(&arr[i]);
        i=i+2;
        j++;
    }
    return retArr;
}

// count the number of levels specified
int NumLvl(char* arr){
    int i = 0;
    while(arr[i]){
        i++;
    }
    return i-(i/2);
}