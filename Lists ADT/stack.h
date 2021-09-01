#ifndef STACK_H
#define STACK_H

#include "array_list.h"
#include <stdexcept>

template <typename Object>
class Stack {
   private:
      ArrayList<Object> stack;
      size_t count;

   public:
      Stack();
      Stack(const Stack& copy);
      ~Stack();
      Stack& operator=(const Stack& copy);
      void push(const Object& data);
      void pop(); // throw std::out_of_range if the stack is empty.
      Object& top(); //std::out_of_range if stack is empty
      size_t size1() const;
};


template <typename Object>
Stack<Object>::Stack():count(0){}

template <typename Object>
Stack<Object>::Stack(const Stack& copy){
   this->count = copy.count;
   this->stack = copy.stack;
}

template <typename Object>
Stack<Object>::~Stack(){}

template <typename Object>
Stack<Object>& Stack<Object>::operator=(const Stack& copy){
   this->count = copy.count;
   this->stack = copy.stack;
   return *this;
}

template <typename Object>
void Stack<Object>::push(const Object& data){
   stack.insert(stack.size(),data);
   count += 1;
}

template <typename Object>
void Stack<Object>::pop(){
   stack.remove(stack.size()-1);
   count -=1;
}

template <typename Object>
Object& Stack<Object>::top(){
   return stack[stack.size()-1];
}

template <typename Object>
size_t Stack<Object>::size1() const{
   return count;
}



#endif  // STACK_H