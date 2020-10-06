#ifndef ALLOCATIONSTRATEGY_H
#define ALLOCATIONSTRATEGY_H

#include "LinkedList.h"

class AllocationStrategy {
    public:

    AllocationStrategy();

    virtual ~AllocationStrategy();

    virtual bool perform(std::string name) = 0;

    LinkedList* getAllocMBList();
    
    LinkedList* getFreedMBList();

    void updateTotalMemory(int offSet);

    void print(std::string fileName);

    int getCurrentId();

    void updateId();

    protected:

    int currentId;

    LinkedList* allocMBList;

    LinkedList* freedMBList;

    int totalMemory;

};

#endif // ALLOCATIONSTRATEGY_H