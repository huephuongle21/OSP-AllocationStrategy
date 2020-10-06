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

   /**
    * output: Get the value at the given index.
    * input: Index must be >=0 and < size()
    * 
    */
   MemoryBlock* get(const int index) const;

   /**
    * Add the value to the back of the Linked List
    */
   void addBack(MemoryBlock* block);

   void addBackFreedMBList(MemoryBlock* block);

   void setSize(int offSet);

   void merge(Node* prev, Node* curr, Node* next);

   /**
    * Removes all values from the Linked List
    */
   void clear();

   Node* getHead();

   void printFreedMBList(std::ostream& outStream);

   void printAllocMBList(std::ostream& outStream);

   void setHead(Node* newHead);

private:

   Node* head;
   int length;
};

#endif // LINKED_LIST_H
