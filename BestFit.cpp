#include "BestFit.h"
#include <limits.h>

BestFit::~BestFit() {
    
}

bool BestFit::perform(std::string name) {
    bool isAllocated = false;

    // Create variables to store the best fit memory block
    int min_gap = INT_MAX;
    MemoryBlock* bestFit = nullptr;

    // Get size of the new name
    size_t size = strlen(name.c_str());

    // Search the entire list to get the smallest hole which is big enough
    Node* head = freedMBList->getHead();
    while(head != nullptr) {
        MemoryBlock* copy = head->value;
        int gap = copy->getSize() - size;
        if(gap < min_gap && gap >= 0) {
            min_gap = gap;
            bestFit = copy;
        }
        head = head->next;
    }

    // If the best-fit hole found
    if(bestFit != nullptr) {
        // Allocate memory directly if the leftover is 0
        if(min_gap == 0) {
            allocateMemoryToHole(freedMBList, allocMBList, name, bestFit);
        } else {
            // Split the hole
            splitHole(name, freedMBList, allocMBList, bestFit, min_gap);
        }
        // Return true as memory is allocated
        isAllocated = true;
    }

    return isAllocated;
}
