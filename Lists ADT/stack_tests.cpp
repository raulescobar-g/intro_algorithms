#include <iostream>
#include "stack.h"

int main() {
    // make an empty stack
    Stack<int> stacky;

    // push 0-29 values onto the stack
    for (int i = 0; i < 50; ++i){
        stacky.push(i);
        std::cout<< stacky.top()<<",";
    }
    std::cout<<std::endl<<"Size: "<<stacky.size1()<<std::endl;
    

    for (int i = 0; i < 25; ++i){
        stacky.pop();
        std::cout<< stacky.top()<<std::endl;
        std::cout<<"Size: "<<stacky.size1()<<std::endl;
    }


    Stack<int> stack_copy(stacky);
    Stack<int> stack_equal;
    stack_equal = stacky;
    std::cout<<"Copy | operator"<<std::endl;
    std::cout<<stack_copy.top()<<" "<<stack_equal.top()<<std::endl;
    
    //remove the rest
    for (int i = 0; i < 10; ++i){
        stacky.pop();
        std::cout<< stacky.top()<<",";
    }
    std::cout<<std::endl;


    std::cout<<"Copy | operator"<<std::endl;
    std::cout<<stack_copy.top()<<" "<<stack_equal.top()<<std::endl;
    try{
        for (int i = 0; i< 100; ++i){
            stacky.pop();
        }
    }
    catch (std::out_of_range(e)){
        std::cout<<e.what()<<std::endl;
    }
    try{
        stacky.top();
    }
    catch (std::out_of_range(e)){
        std::cout<<e.what()<<std::endl;
    }


    return 0;
}
