#include "MemoryBlock.h"
#include "Utility.h"
#include <iomanip>

MemoryBlock::MemoryBlock(int id, void* wpt, int wsize, std::string content) {
    this->wpt = wpt;
    this->wsize = wsize;
    this->content = content;
    this->id = id;
}

MemoryBlock::MemoryBlock() {

}

MemoryBlock::~MemoryBlock() {

}

MemoryBlock::MemoryBlock(const MemoryBlock& other) {
   this->wpt = other.wpt;
   this->wsize = other.wsize;
   this->content = other.content;
   this->id = other.id;
}

void MemoryBlock::setSize(int wsize) {
    this->wsize = wsize;
}

void MemoryBlock::setAddress(void* wpt) {
    this->wpt = wpt;
}

void MemoryBlock::setContent(std::string content) {
    this->content = content;
}

void MemoryBlock::setId(int id) {
    this->id = id;
}

void* MemoryBlock::getAddress() {
    return this->wpt;
}

int MemoryBlock::getSize() {
    return this->wsize;
}

std::string MemoryBlock::getContent() {
    return this->content;
}

int MemoryBlock::getId() {
    return this->id;
}

void MemoryBlock::printBlockInFreedMBList(std::ostream& outStream) {
    outStream << "  " << std::left << std::setw(4) << wpt << "  |";
    outStream << "  " << std::left << std::setw(4) << wsize << std::endl;
}

void MemoryBlock::printBlockInAllocMBList(std::ostream& outStream) {
    if(content != EMPTY_BLOCK) {
        outStream << "  " << std::left << std::setw(4) << wpt << "  |";
        outStream << "  " << std::left << std::setw(4) << wsize << "  |";
        outStream << "  " << std::left << std::setw(1) << content;
        outStream << std::endl;
    }
}   