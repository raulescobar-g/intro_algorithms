#include "array_list.h"
#include <iostream>

int main(){
    std::cout<<"Declaring list.."<<std::endl;
    // make an empty list
    ArrayList<int> list;

    std::cout<<"Inserting into base list..."<<std::endl;
    for (size_t i = 0; i < 50; ++i){
        list.insert(i,10);
        std::cout<<list[i]<<",";
    }
    std::cout<<std::endl<<"Inserting done."<<std::endl;
    size_t size = list.size();
    std::cout<<"Removing..."<<std::endl;
    for (size_t i = 0; i < 20; ++i){
        list.remove(i);
    }
    std::cout<<"Re-print after deletion in intervals of 3..."<<std::endl;
    size = list.size();
    for (size_t i = 0; i < size; ++i){
        std::cout<<list[i]<<",";
    }
    size = list.size();
    std::cout<<"Size of base list: "<<size<<std::endl;
    //list = list;

    ArrayList<int> list_copy(list);
    ArrayList<int> list_copy2 = list;
    size_t size1 = list_copy.size();
    size_t size2 = list_copy2.size();
    std::cout<<"Printing out copies..."<<std::endl;
    for (size_t i = 0; i < size1; ++i){
        std::cout<<list_copy[i]<<",";
    }
    std::cout<<std::endl;
    for (size_t i = 0; i < size2; ++i){
        std::cout<<list_copy2[i]<<",";
    }
    std::cout<<std::endl;
    
    std::cout<<"Output Messages: "<<std::endl;
    try{
        list[500];
    }
    catch (std::out_of_range(e)){
        std::cout<<e.what()<<std::endl;
    }
    try{
        list_copy.remove(100);
    }
    catch (std::out_of_range(e)){
        std::cout<<e.what()<<std::endl;
    }
    try{
        list_copy2.insert(100,200);
    }
    catch (std::out_of_range(e)){
        std::cout<<e.what()<<std::endl;
    }
    

    return 0;
}