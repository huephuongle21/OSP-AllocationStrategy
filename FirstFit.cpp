#include "FirstFit.h"

FirstFit::~FirstFit() {
    
}

bool FirstFit::perform(std::string name) {
    bool isAllocated = false;

    // Get the size of new name
    size_t size = strlen(name.c_str());

    // Get the start of sets of holes
    Node* head = freedMBList->getHead();

    // Search to find the first hole which is large enough
    while(head != nullptr) {
        MemoryBlock* copy = head->value;
        int gap = copy->getSize() - size;

        // Allocate memory if the first large enough hole is found
        if(gap >= 0) {
            // Allocate memory directly if the leftover is 0
            if(gap == 0) {
                allocateMemoryToHole(freedMBList, allocMBList, name, copy);
            } else {
                // Split the hole
                splitHole(name, freedMBList, allocMBList, copy, gap);
            }
            // Return true as memory is allocated
            isAllocated = true;
            break;
        }
        // Continue searching if hole not found yet
        head = head->next;
    }
    return isAllocated;
}
