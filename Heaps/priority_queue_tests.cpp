#include "priority_queue.h"

#include <iostream>
#include <vector>



int main() {

    std::vector<int> q;
    std::vector<int> fail;
    std::vector<std::string> a{"one","two","three","four","five","six","seven","eight","nine","ten"};

    
    for (int i = 100; i > 0; --i){
        q.push_back(i);
    }
    
    std::cout<<"heapify time: "<<std::endl;
    PriorityQueue<int> prio(q);
    PriorityQueue<int> prio1(fail);
    PriorityQueue<std::string> prio2(a);
    std::cout<<"heapifying done. "<<std::endl;

    prio.print_queue();
    prio1.print_queue();
    prio2.print_queue();

    std::cout<<"Checking the heapify, size,top, and pop..."<<std::endl;
    for (size_t i = 1; i <= 100; ++i){
        if (prio.size() != (size_t)100-i+1){
            std::cout<<"error in size"<<std::endl;
        }
        int a = prio.top();
        if ((int)i != a){
            std::cout<<"error in pop or top"<<std::endl;
        }
        prio.pop();
    }
    std::cout<<"Printing heap after removing everything..."<<std::endl;
    prio.print_queue();



    try{
        prio1.top();
    }
    catch (std::invalid_argument(e)){
        std::cout<<e.what()<<std::endl;
    }
    try{
        prio.pop();
    }
    catch (std::invalid_argument(e)){
        std::cout<<e.what()<<std::endl;
    }



    if (prio2.top() != "eight"){
        std::cout<<"check string tree for smallest value"<<std::endl;
    }
    prio2.pop();
    if (prio2.top() == "eight"){
        std::cout<<"check pop for string heap"<<std::endl;
    }
    


    std::cout<<"Checking the push"<<std::endl;
    for (int i = 1; i <= 100; ++i){
        prio.push(i);
    }
    std::cout<<"check for double zeors in the beginning"<<std::endl;
    prio.print_queue();

    prio.make_empty();

    std::cout<<"size after calling .make_empty(): "<<prio.size()<<std::endl;
    prio.print_queue();


    std::cout<<"Calling print after inserting 30 elements :"<<std::endl;
    for (int i = 1; i < 31; ++i ){
        prio.push(i);
    }
    prio.print_queue();

    PriorityQueue<int> p;
    p.pop();




    return 0;
}
