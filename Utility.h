#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string.h>
#include "MemoryBlock.h"
#include "LinkedList.h"
#include "AllocationStrategy.h"
#include <vector>

#define EMPTY_BLOCK             "_"
#define NUM_READ_NAMES          1000
#define NUM_DELETE_NAMES        500

void readFile(std::vector<std::string>& names, std::string filename);

void shuffle(int* randomNumbers, int size);

void swap(int& a, int& b);

void generateRandomDeletedNumbers(int* numbers, unsigned int size);

// Allocate for the first 1000 names and deletes randomly 500 names
void initialSetup(AllocationStrategy* strategy, std::vector<std::string>& names, int* numbers, unsigned int size);

// Allocate new memory block using sbrk
void allocateNewMemory(AllocationStrategy* strategy, std::string name);

// Deallocate memory
void deallocateMemory(LinkedList* allocMBList, LinkedList* freedMBList, int* numbers, unsigned int size);

// Allocate memory to the hole when the size of the hole is similar to the new name
void allocateMemoryToHole(LinkedList* freedMBList, LinkedList* allocMBList, std::string name, MemoryBlock* hole);

// Split hole to allocate memory when size of the hole is larger
void splitHole(std::string name, LinkedList* freedMBList, LinkedList* allocMBList, MemoryBlock* hole, int gap);

// Add the hole back to allocMBList after allocating
void updateAllocFromFreed(LinkedList* allocMBList, MemoryBlock* hole, std::string name, int size);

void perform(AllocationStrategy* strategy, std::vector<std::string>& names, int* numbers);

#endif // UTILITY_H