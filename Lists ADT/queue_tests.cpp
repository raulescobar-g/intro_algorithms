#include <iostream>
#include "queue.h"

int main() {
    //make an empty queue
    Queue<int> queue;

    // enqueue 3 values into the queue
    for (int i = 0; i < 50;++i){
        queue.enqueue(i);
    }
    std::cout<<"Size: "<<queue.size1()<<std::endl;
    
    
    Queue<int> queue1(queue);
    Queue<int> queue2;
    queue2 = queue;
    std::cout<<"Size: "<<queue1.size1()<<std::endl;
    std::cout<<"Size: "<<queue2.size1()<<std::endl;
    for (int i = 0; i < 25; ++i){
        std::cout<<queue.dequeue()<<",";
    }

    std::cout<<std::endl<<"Size: "<<queue.size1()<<std::endl;
    std::cout<<"Size: "<<queue1.size1()<<std::endl;
    std::cout<<"Size: "<<queue2.size1()<<std::endl;
    for (int i = 0; i < 25; ++i){
        std::cout<<queue1.dequeue()<<",";
    }
    std::cout<<std::endl<<"Size: "<<queue1.size1()<<std::endl;





    
    return 0;
}
