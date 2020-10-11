#include "Utility.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <math.h>

void readFile(std::vector<std::string>& names, std::string filename) {
    std::string line;
    std::ifstream inFile;
    inFile.open(filename);
    if(inFile.fail()) {
        std::cout << "File does not exist!" << std::endl;
    } else {
        while(!inFile.eof() && std::getline(inFile, line)) {
            names.push_back(line);
        }
        inFile.close();
    }
}

void shuffle(int* randomNumbers, int size) {
    for (int i = size - 1; i > 0; --i)  {      
        // Pick a random index from 0 to i  
        int j = rand() % (i + 1);
        // Swap arr[i] with the element at random index  
        swap(randomNumbers[j], randomNumbers[i]);
    } 
}

void swap(int &a, int &b)  {  
    int tmp = a;  
    a = b;  
    b = tmp;
}

void generateRandomDeletedNumbers(int* numbers, unsigned int size) {
    for(unsigned int i = 0; i != size; i++) {
        numbers[i] = i;
    }
    shuffle(numbers, size);
}

void allocateMemoryToHole(LinkedList* freedMBList, LinkedList* allocMBList, 
        std::string name, MemoryBlock* hole) {
    
    hole->setContent(name);

    // Update allocMBList
    updateAllocFromFreed(allocMBList, hole, name, hole->getSize());

    // Delete the block in freedMBList
    Node* head = freedMBList->getHead();
    if(head != nullptr && head->value->getAddress() == hole->getAddress()) {
        // Set head of linked list to head->next
        freedMBList->setHead(head->next);
    } else {
        Node* prev = head;
        Node* current = head->next;
        Node* next = current->next;
        while(current != nullptr) {
            if(current->value->getAddress() == hole->getAddress()) {
                break;
            } else {
                prev = current;
                current = prev->next;
                next = current->next;
            }
        }
        prev->next = next;
    }
    freedMBList->setSize(-1);
}

void updateAllocFromFreed(LinkedList* allocMBList, MemoryBlock* hole, 
        std::string name, int size) {
    // Allocate memory to the hole in allocMBList
    bool isAllocated = false;
    Node* allocHead = allocMBList->getHead();
    while(allocHead != nullptr) {
        MemoryBlock* block = allocHead->value;
        if(block->getAddress() == hole->getAddress() 
                && block->getContent() == EMPTY_BLOCK) {
            block->setContent(name);
            block->setSize(size);
            isAllocated = true;
            break;
        } else {
            allocHead = allocHead->next;
        }
    }

    // Add new hole to allocMBList if the picked hole was created 
    // by spliting existing one
    if(!isAllocated) {
        MemoryBlock* copy = new MemoryBlock(*hole);
        allocMBList->addAllocMBList(copy);
    }
}

void splitHole(std::string name, LinkedList* freedMBList, 
        LinkedList* allocMBList, MemoryBlock* hole, int gap) {
    // Get the size of new content
    size_t size = strlen(name.c_str());

    // Create new memory block with the leftover
    void* request = hole->getAddress();
    void* leftover = (char*)request + size;

    // Allocate memory to the hole in allocMBList
    hole->setContent(name);
    hole->setSize(size);
    updateAllocFromFreed(allocMBList, hole, name, size);

    // Replace the hole from freedMBList
    hole->setAddress(leftover);
    hole->setSize(gap);
    hole->setContent(EMPTY_BLOCK);
}

void initialSetup(AllocationStrategy* strategy, std::vector<std::string>& names, 
        int* numbers, unsigned int size) {

    LinkedList* allocMBList = strategy->getAllocMBList();
    LinkedList* freedMBList = strategy->getFreedMBList();

    // Read the first 1000 names and allocate memory directly using sbrk
    for(int i = 0; i != NUM_READ_NAMES; i++) {
        allocateNewMemory(strategy, names[i]);
    }

    // Randomly delete 500 names
    deallocateMemory(allocMBList, freedMBList, numbers, size);
}

void allocateNewMemory(AllocationStrategy* strategy, std::string name) {
    LinkedList* allocMBList = strategy->getAllocMBList();

    // Get size of the name and allocate new memory using sbrk
    size_t size = strlen(name.c_str());
    void* request;
    request = sbrk(size);

    // Create new memory block and update allocMBList
    MemoryBlock* block = new MemoryBlock(strategy->getCurrentId(), request, size, name);
    strategy->updateId();
    allocMBList->addAllocMBList(block);

    // Update total memory allocated
    strategy->updateTotalMemory(size);
}

void deallocateMemory(LinkedList* allocMBList, LinkedList* freedMBList, 
        int* numbers, unsigned int size) {
    // Randomly delete 500 names
    int count = 0;
    for(unsigned int i = 0; i != size; i++) {
        MemoryBlock* block = allocMBList->get(numbers[i]);
        if(block != nullptr && block->getContent() != EMPTY_BLOCK) {
            // Set the content of the block in allocMBList to empty
            block->setContent(EMPTY_BLOCK);
            MemoryBlock* copy = new MemoryBlock(*block);

            // Add block to freedMBList
            freedMBList->addFreedMBList(copy);
            count++;            
        }
        if(count == NUM_DELETE_NAMES) {
            break;
        }
    }
}

void perform(AllocationStrategy* strategy, std::vector<std::string>& names, int* numbers) {
    LinkedList* allocMBList = strategy->getAllocMBList();
    LinkedList* freedMBList = strategy->getFreedMBList();

    unsigned int size = names.size();

    // Read the first 1000 names and delete randomly 500 names
    initialSetup(strategy, names, numbers, size);

    int totalReadName = NUM_READ_NAMES;
    int eachTimeReadName = 0;

    int totalNames = size;

    // Loop to perform allocate and deallocate multiple times
    while(totalReadName != totalNames) {
        // Read 1000 names
        while(eachTimeReadName != NUM_READ_NAMES) {
            // Try to allocate memory using the algorithm, if no available hole found,
            // allocate new memory
            if(!strategy->perform(names[totalReadName])) {
                allocateNewMemory(strategy, names[totalReadName]);
            }
            // Update index
            totalReadName++;
            eachTimeReadName++;
            if(totalReadName == totalNames) {
                break;
            }
        }
        // Delete 500 names if already allocate for 1000 names
        if(eachTimeReadName == NUM_READ_NAMES) {
            deallocateMemory(allocMBList, freedMBList, numbers, size);
            eachTimeReadName = 0;
        }
    }
}