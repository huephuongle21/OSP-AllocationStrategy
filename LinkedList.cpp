#include "LinkedList.h"

#include <exception>

Node::Node(MemoryBlock* value, Node* next) {
    this->value = value;
    this->next = next;
}

Node::~Node() {

}

LinkedList::LinkedList() {
   this->head = nullptr;
   this->length = 0;

}

LinkedList::~LinkedList() {
   clear();
}

MemoryBlock* LinkedList::get(const int index) const {
   int count = 0;
   Node* current = head;
   MemoryBlock* returnValue = nullptr;
   
   if (index < length) {     
      while(count < index) {
        ++count;
        current = current->next;
      }
      returnValue = current->value;      
   } 
   return returnValue;
}

void LinkedList::addBack(MemoryBlock* block) {   
   Node* toAdd = new Node(block, nullptr);
   if (head == nullptr) {
      head = toAdd;
   } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
      }
      current->next = toAdd;
   }
   ++length;
}

void LinkedList::setSize(int offSet) {
   length += offSet;
}

void LinkedList::addBackFreedMBList(MemoryBlock* block) {
   Node* toAdd = new Node(block, nullptr);
   if(head == nullptr || head->value->getId() >= block->getId()) { 
      toAdd->next = head; 
      head = toAdd; 
      if(head->next != nullptr) {
         merge(head, head->next, nullptr);
      }
   }  else {
      Node* current = head; 
      while (current->next != nullptr 
            && current->next->value->getId() < block->getId()) { 
         current = current->next; 
      } 
      toAdd->next = current->next; 
      current->next = toAdd; 
      merge(current, toAdd, toAdd->next);
   } 
   ++length;
}

void LinkedList::merge(Node* prev, Node* curr, Node* next) {
   MemoryBlock* bPrev = prev->value;
   MemoryBlock* bCurr = curr->value;
   MemoryBlock* bNext = nullptr;
   if(next != nullptr) {
      bNext = next->value;
   }
   bool isMerge = false;
   if((char*)bPrev->getAddress() + bPrev->getSize() == (char*)bCurr->getAddress()) {
      bPrev->setSize(bPrev->getSize() + bCurr->getSize());
      prev->next = next;
      --length;
      isMerge = true;
   }
   if(!isMerge && bNext != nullptr) {
      if((char*)bCurr->getAddress() + bCurr->getSize() == (char*)bNext->getAddress()) {
         bCurr->setSize(bCurr->getSize() + bNext->getSize());
         curr->next = next->next;
         --length;
      }
   } else if(isMerge && bNext != nullptr) {
      if((char*)bPrev->getAddress() + bPrev->getSize() == (char*)bNext->getAddress()) {
         bPrev->setSize(bPrev->getSize() + bNext->getSize());
         prev->next = next->next;
         --length;
      }
   }
}

void LinkedList::clear() {
   while (length > 0) {
      Node* newHead = head->next;
      delete head;
      head = newHead;
      --length;
   }
}

Node* LinkedList::getHead() {
   return this->head;
}

void LinkedList::printFreedMBList(std::ostream& outStream) {
   Node* head = getHead();
   while(head != nullptr) {
      head->value->printBlockInFreedMBList(outStream);
      head = head->next;
   }
}

void LinkedList::printAllocMBList(std::ostream& outStream) {
   Node* head = getHead();
   while(head != nullptr) {
      head->value->printBlockInAllocMBList(outStream);
      head = head->next;
   }
}

void LinkedList::setHead(Node* newHead) {
   head = newHead;
}