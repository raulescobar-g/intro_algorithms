#include "heap.h"
#include <iostream>
#include <vector>
#include <deque>

int main() {
    std::vector<int> heap;
    for (int i = 100; i > 0; --i){
        heap.push_back(i);
    }

    //std::cout << "before heapify: ";
    //for (int i : heap) { std::cout << i << " "; }
    //std::cout << std::endl;

    heapify(&heap);

    //std::cout << "after heapify: ";
    //for (int i : heap) { std::cout << i << " "; }
    //std::cout << std::endl;

    //std::cout<<"deleting all elements..."<<std::endl;
    for (int j = 1; j < 101; j++) {
        if (heap_get_min(heap) != j){
            std::cout<<"heapify or delete error..."<<std::endl;
        }
        heap_delete_min(&heap);
    }

    //for (int i : heap) { std::cout << i << " "; }
    //std::cout << std::endl;

    
    for (int i = 100; i > 0; --i){
        heap_insert(&heap,i);
    }
    //std::cout<<"heap after 100 manual insertions..."<<std::endl;
    //for (int i : heap) { std::cout << i << " "; }
    //std::cout << std::endl;

    //std::cout<<"deleting all elements..."<<std::endl;
    for (int j = 1; j < 101; j++) {
        if (heap_get_min(heap) != j){
            std::cout<<"heapify or delete error..."<<std::endl;
        }
        heap_delete_min(&heap);
    }

    //for (int i : heap) { std::cout << i << " "; }
    //std::cout << std::endl;
        


    std::cout<<"testing error messages [2]: "<<std::endl;
    try{
        heap_delete_min(&heap);
    }
    catch (std::invalid_argument(e)){
        std::cout<<e.what()<<std::endl;
    }
    try{
        heap_get_min(heap);
    }
    catch (std::invalid_argument(e)){
        std::cout<<e.what()<<std::endl;
    }



    std::cout<<"testing deletion..."<<std::endl;
    std::vector<int> heap1{1000000,3,7,5,8,6,1,1,22,77,23,56,78,12,2,65,666,78,9,20,330,40,200,65,34,56,778,11,12,56};
    heapify(&heap1);

    for (int i = 0; i < 30; ++i){
    std::cout<<"Min is :             -> "<<heap_get_min(heap1)<<std::endl<<" , and after delete heap is: "<<std::endl;
    heap_delete_min(&heap1);
    for (int i : heap1) { std::cout << i << " "; }
    std::cout << std::endl;
    }
    




    return 0;
}
