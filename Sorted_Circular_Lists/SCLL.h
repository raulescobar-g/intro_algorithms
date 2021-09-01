// SCLL.h
#ifndef SCLL_H
#define SCLL_H

#include <iostream>
#include "Node.h"

template <typename T>
class SortedCircularList {
  Node<T>* head;  
  Node<T>* tail;
public:
  SortedCircularList() : head(nullptr), tail(nullptr) {}
  void print(std::ostream& out=std::cout) const;
  // insert val into a sorted circular list
  void insertValue(const T& val);
};

// print function
template <typename T>
void SortedCircularList<T>::print(std::ostream& out) const {
   Node<T>* current=head;
   if (current!=nullptr) {
      out<<current->data<<" ";
      while(current->next != head)
   {
         current = current->next;   
         out<<current->data<<" ";
      }
   }
}

// WRITE THIS FUNCTION
template <typename T>
void SortedCircularList<T>::insertValue(const T& val)  {
    //create Node; create the pointer that runs through list; create a pointer that lags
    Node<T> *newNode = new Node<T>(val);
    Node<T> *iterator = head;
    Node<T> *lag = tail;
    

    if (head != nullptr){
      //if its not empty then add a node
      //check that its not at hte end of the list and see if its greater or less than hte last data point
      if (iterator->next == head && iterator->data <= newNode->data){
        iterator->next = newNode;
        tail = newNode;
        newNode->next = head;
      }
      //check to see if its at the end of the list and if its greter or less htan data point
      else if (iterator->next == head && iterator->data > newNode->data){
        head = newNode;
        newNode->next = iterator;
        iterator->next = head;
      }
      else{
        while(iterator->data < newNode->data){
          //check that its not infinite loop
          if (iterator->next == head){
            tail = newNode;
            iterator->next = newNode;
            newNode->next = head;
            break;
          }
          else{
            lag = iterator;
            iterator = iterator->next;
          }
        }
        if (tail != newNode){
          newNode->next = iterator;
          lag->next = newNode;
        }
      }
    }
    else {
      //in this case its empty and we make the head and tail point to the new node
      head = newNode;
      tail = newNode;
      newNode->next = head;
    }
}

#endif