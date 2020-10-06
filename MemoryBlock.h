#ifndef MEMORYBLOCK_H
#define MEMORYBLOCK_H 

#include <string.h>
#include <iostream>

class MemoryBlock {
public:
    MemoryBlock(int id, void* wpt, int wsize, std::string content);
    MemoryBlock();
    MemoryBlock(const MemoryBlock& other);
    ~MemoryBlock();

    void setSize(int wsize);
    void setAddress(void* wpt);
    void setContent(std::string content);
    void setId(int id);

    int getSize();
    void* getAddress();
    std::string getContent();
    int getId();

    void printBlockInFreedMBList(std::ostream& outStream);

    void printBlockInAllocMBList(std::ostream& outStream);

private:
    int wsize;
    void* wpt;
    std::string content;
    int id;
};

#endif // MEMORYBLOCK_H