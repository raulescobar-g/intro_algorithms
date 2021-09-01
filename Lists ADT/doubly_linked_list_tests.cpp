#include <iostream>
#include "doubly_linked_list.h"



int main(){
    // make an empty list
    std::cout<<"Declaring 1 lists..."<<std::endl;
    DoublyLinkedList<int> list;
    std::cout<<"size: "<<list.size()<<list.size()<<std::endl;
    

    // insert 3 values at the end of the list
    std::cout<<"Inserting into base list..."<<std::endl;
    for (size_t i = 0; i<50 ; ++i){
        list.insert(i,i);
        std::cout<<list[i]<<",";
    }
    std::cout<<"Inserting done. Removing now..."<<std::endl;
    list.remove(list.size()-1);
    list.remove(0);
    for (size_t i = 10; i<20 ; ++i){
        list.remove(i);
    }
    std::cout<<"List after removing first,last and mid 10: "<<std::endl;
    for (size_t i = 0; i<list.size();++i){
        std::cout<<list[i]<<",";
    }
    DoublyLinkedList<int> list2(list);
    DoublyLinkedList<int> list3;
    list3=list2;
    for (size_t i = 0; i < 40; ++i){
        list2.insert(i%list2.size(),i);
        list3.insert(i%list3.size(),i);
        list2.remove(i%list2.size());
        list3.remove(i%list3.size());
    }
    list2 = list3;
    
    std::cout<<"Copy list sizes: "<<list2.size()<<" ,"<<list3.size()<<std::endl;
    list2.remove(list2.size()-1);
    list2.remove(0);
    list3.remove(list3.size()-1);
    list3.remove(0);
    std::cout<<"Removing from copies..."<<std::endl;
    for (size_t i = 10; i<20 ; ++i){
        list2.remove(i);
        list3.remove(i);
    }
    
    std::cout<<"Copy list sizes after removal: "<<list2.size()<<" ,"<<list3.size()<<std::endl;
    //list = list;
    while (list.size() != 0){
        list.remove(0);
    }
    while (list2.size() != 0){
        list2.remove(list2.size()-1);
    }
    while (list3.size() != 0){
        list3.remove(list3.size()/2);
    }
    std::cout<<"list sizes after empty: "<<list.size()<<", "<<list2.size()<<" ,"<<list3.size()<<std::endl;

    
    
    std::cout<<"Error messages output: "<<std::endl;
    try{
        list[1000];
    }
    catch (std::out_of_range(e)){
        std::cout<<e.what()<<std::endl;
    }
    try{
        list.insert(10000,1);
    }
    catch (std::out_of_range(e)){
        std::cout<<e.what()<<std::endl;
    }
    try{
        list.remove(10000);
    }
    catch (std::out_of_range(e)){
        std::cout<<e.what()<<std::endl;
    }



    return 0;
}












