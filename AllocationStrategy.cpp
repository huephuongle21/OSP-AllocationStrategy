#include "AllocationStrategy.h"
#include <fstream>

AllocationStrategy::AllocationStrategy() {
    allocMBList = new LinkedList();
    freedMBList = new LinkedList();
    totalMemory = 0;
    currentId = 1;
}

AllocationStrategy::~AllocationStrategy() {

}

LinkedList* AllocationStrategy::getAllocMBList() {
    return allocMBList;
}

LinkedList* AllocationStrategy::getFreedMBList() {
    return freedMBList;
}

void AllocationStrategy::updateTotalMemory(int offSet) {
    totalMemory += offSet;
}

int AllocationStrategy::getCurrentId() {
    return this->currentId;
}

void AllocationStrategy::updateId() {
    currentId++;
}

void AllocationStrategy::print(std::string fileName) {
    std::ofstream os;
    os.open(fileName);
    if(os.fail()) {
        std::cout << "\nCould not create save.\n\n";
    } else {
        os << "Total memory allocated: " << totalMemory << "\n" << std::endl;
        os << "Print freedMBList:\n\n";
        freedMBList->printFreedMBList(os);
        os << std::endl;
        os << "Print allocMBList:\n\n";
        allocMBList->printAllocMBList(os);
        os << std::endl;

        os.close();
    }
}