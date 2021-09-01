#include "heap.h"

#include <vector>
#include <iostream>


using namespace std::chrono;




int main(){

    std::vector<int> a;
    

    for (int j = 1000; j < 100000; j*=2){
        
        for (int i = j; i > 0; --i){
            a.push_back(i);
        }


        auto start = std::chrono::high_resolution_clock::now();
        heapify(&a);
        auto diff = std::chrono::high_resolution_clock::now() - start;
    
    
        auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);
        std::cout << "for N=" <<a.size()<<" heapifies in : "<< t1.count() <<" ns"<< std::endl;
        
        
        a.clear();
    }


    for (int j = 10000; j < 10000000; j*= 2){
        
        for (int i = j; i > 1; --i){
            a.push_back(i);
        }
        heapify(&a);

        auto start = std::chrono::high_resolution_clock::now();
        heap_delete_min(&a);
        auto diff = std::chrono::high_resolution_clock::now() - start;
    
    
        auto t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);
        std::cout << "for N=" <<a.size()<<" deleete 1 element in : "<< t1.count() << " ns"<<std::endl;

        a.clear();

    }



    return 0;
}






























































