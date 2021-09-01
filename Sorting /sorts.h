#ifndef SORTS_H
#define SORTS_H

#include "heap.h"
#include <functional> 
#include <iostream> 
#include <vector> 
#include <utility>

// Pretty printing for vectors of Printable objects (have ostream operator<< defined)
// Be careful: modifications risk failing tests
template <class Printable>
std::ostream& operator<<(std::ostream& os, const std::vector<Printable>& container) {
    os << "[";
    bool first = false;
    for (const Printable& t : container) {
        if (first) {
            os << ", ";
        }
        if (typeid(t) == typeid(std::string)) {
            os << "\"" << t << "\"";
        } else {
            os << t;
        }
        first = true;
    }
    os << "]";
    return os;
}

// Selection sort (example of implementation expectations)
template <class Comparable>
void selection_sort(std::vector<Comparable>& container) {
    // print the initial container
    std::cout << container << std::endl;
    
    if (container.empty()) {
        return;
    }

    for (size_t index = 0; index < container.size()-1; index++) {
        // do 1 pass of selection sort: find the min and swap it to the front
        size_t index_min = index;
        for (size_t i = index+1; i < container.size(); i++) {
            if (container[i] < container[index_min]) {
                index_min = i;
            }
        }
        Comparable t = container[index];
        container[index] = container[index_min];
        container[index_min] = t;
        
        // print the container after each pass
        std::cout << container << std::endl;
    }
}

// TODO(student): implement 4 sorts from: insertion, shell, heap, merge, quick, bucket, radix


template <class Comparable>
void show(std::vector<Comparable>& container){
    std::cout<<"[";
    for (int i = 0; i < container.size()-1; ++i){
        std::cout<<container[i]<<",";
    }
    std::cout<<container[container.size()-1]<<"]"<<std::endl;
}

int exp(int power){
    int result = 1;
    int base = 2;
    while(power > 0) {
        if(power % 2 == 1) { 
            result *= base;
        }
        base = (base * base);
        power /= 2;
    }
    return result;
}

int first_hibbard(int num){
    int count = -1;
    while (num > 0){
        num /= 2;
        count += 1;
    }
    return count;
}

int hibbard(int num){
    return exp(num)-1;
}

template <class Comparable>
void insertion_sort(std::vector<Comparable>& container){
    
    std::cout<<container<<std::endl;
    if (container.empty()) {
        return;
    }
    
    
    for (int i = 1; i < container.size(); ++i){
        Comparable var = std::move(container[i]);

        int j;
        for (j = i; j > 0 && var < container[j-1]; --j){
            container [j] = std::move(container[j-1]); 
        }
        container[j] = std::move(var);
        std::cout << container << std::endl;
    }
}


template <class Comparable>
void heap_sort(std::vector<Comparable>& container){
    std::cout << container << std::endl;
    if (container.empty()) {
        return;
    }
    heapify(&container);
    std::cout << container << std::endl;
    std::vector<Comparable> tmp;
    while(container.size() > 1){
        tmp.push_back(heap_get_min(container));
        heap_delete_min(&container);
        
        std::cout <<container << std::endl;
        std::cout <<tmp << std::endl;
    }
    container = std::move(tmp);
}

template <class Comparable>
void merge_sort(std::vector<Comparable>& container){}

template <class Comparable>
void radix_sort(std::vector<Comparable>& container){}

template <class Comparable>
void quick_sort(std::vector<Comparable>& container){}

template <class Comparable>
void shell_sort(std::vector<Comparable>& container){
    std::cout << container << std::endl;
    if (container.empty()) {
        return;
    }
    int k = first_hibbard(container.size());
    //std::cout<<k<<std::endl;
    while (k > 0){
        
        int gap = hibbard(k);
        //std::cout<<"gap size; "<<gap<<std::endl;
        for (int i = gap; i < container.size(); ++i){
            Comparable tmp = std::move(container[ i ]);

            int j = i;
            for( ; j >= gap && tmp < container[j - gap]; j -= gap ){
                container[j] = std::move(container[j - gap]);
            }
            container[j] = std::move(tmp);
        }
        k -= 1;
        std::cout << container << std::endl;
        
    } 
    
}

template <class Comparable>
void bucket_sort(std::vector<Comparable>& container){
     
    std::cout << container << std::endl;
    if (container.empty()) {
        return;
    }
    std::vector<Comparable> count(1,0);

    for (Comparable i : container){
        while (i >= count.size()){
            count.push_back(0);
        }
        count[i] += 1;
        
    }

    std::cout << count << std::endl;
    container.clear();
    bool change = false;
    for (int i = 0; i < count.size(); ++i){
        for (int j = 0; j < count[i]; ++j){
            change = true;
            container.push_back(i);
        }
        if (change){
            std::cout << container << std::endl;
        }
        change = false;
    }
    
}

#endif  // SORTS_H