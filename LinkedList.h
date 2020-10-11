#ifndef LINKED_LIST_H
#define LINKED_LIST_H 

#include "MemoryBlock.h"

class Node {
public:
   Node(MemoryBlock* value, Node* next);
   ~Node();
   MemoryBlock* value;
   Node* next;
};

class LinkedList {
public:
   LinkedList();
   ~LinkedList();

   MemoryBlock* get(const int index) const;

   void addAllocMBList(MemoryBlock* block);
   void addFreedMBList(MemoryBlock* block);

   void setSize(int offSet);

   void merge(Node* prev, Node* curr, Node* next);

   Node* getHead();

   void printFreedMBList(std::ostream& outStream);
   void printAllocMBList(std::ostream& outStream);

   void setHead(Node* newHead);

private:

   Node* head;
   int length;
};

#endif // LINKED_LIST_H
