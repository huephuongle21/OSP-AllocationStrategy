#include "WorstFit.h"
#include <limits.h>

WorstFit::~WorstFit() {
    
}

bool WorstFit::perform(std::string name) {
    bool isAllocated = false;

    // Create variables to store the worst fit memory block
    int max_gap = INT_MIN;
    MemoryBlock* worstFit = nullptr;

    // Get size of the new name
    size_t size = strlen(name.c_str());

    // Search the entire list to get the largest hole which is big enough
    Node* head = freedMBList->getHead();
    while(head != nullptr) {
        MemoryBlock* copy = head->value;
        int gap = copy->getSize() - size;
        if(gap > max_gap && gap >= 0) {
            max_gap = gap;
            worstFit = copy;
        }
        head = head->next;
    }

    // If the worst-fit hole found
    if(worstFit != nullptr) {
        // Allocate memory directly if the leftover is 0
        if(max_gap == 0) {
            allocateMemoryToHole(freedMBList, allocMBList, name, worstFit);
        } else {
            // Split the hole
            splitHole(name, freedMBList, allocMBList, worstFit, max_gap);
        }
        // Return true as memory is allocated
        isAllocated = true;
    }

    return isAllocated;
}
