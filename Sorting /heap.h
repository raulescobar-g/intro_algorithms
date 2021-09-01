#ifndef HEAP_H
#define HEAP_H

#include <functional>
#include <vector>
#include <iostream>

template <class Container, class Compare=std::less<typename Container::value_type> >
void heapify(Container* heap, Compare cmp = std::less<typename Container::value_type>{}){//REPLACE SWAP WITH INSERTS
    
    heap->insert((*heap).begin(),typename Container::value_type{});

    size_t j;
    size_t child;

    for (size_t i = (heap->size()-1)/2; i >= 1; --i){
        j = i;
        child = j*2;
        while (heap->size()-1 >= child){
            if (child != heap->size()-1 && cmp(heap->at(child+1), heap->at(child))){
                child += 1;
            }

            if (cmp(heap->at(child), heap->at(j))){
                typename Container::value_type temp = heap->at(j);
                (*heap)[j] = heap->at(child);
                (*heap)[child] = temp;
                j = child;
                child *= 2;
            }
            else{
                child = heap->size() + 1;
            }
        }
    }
}
//- build a heap with the data in the given container (passed by pointer value to indicate that this function modifies the container) using the specified comparator (comparison functor, default is std::less to make a min heap), the first element of the heap should be in index 1.


template <class Container, class Compare=std::less<typename Container::value_type> >
void heap_insert(Container* heap, const typename Container::value_type& data, Compare compare = std::less<typename Container::value_type>{}){
    if (heap->size() == 0 || heap->at(0) != typename Container::value_type{}){
        heap->insert((*heap).begin(),typename Container::value_type{});
    }
    heap->push_back(data);
    size_t i = heap->size()-1;
    size_t sibling;
    while (i/2 > 0){
        sibling = i-1;
        if (i % 2 == 0 && i < heap->size()-1){
            sibling += 2;
        }
        if (compare(heap->at(sibling), heap->at(i))){
            i = sibling;
        }
        if (compare(heap->at(i), heap->at(i/2))){
            typename Container::value_type temp = heap->at(i);
            (*heap)[i] = heap->at(i/2);
            (*heap)[i/2] = temp;
            i = i/2;
        }
        else{
            return;
        }
    }
} //- insert the specified value into the specified heap (passed by pointer value to indicate that this function modifies the container, which is assumed to already be in heap order with first element in index 1) using the specified comparator (default std::less for a min heap). If the container is empty, do the user a solid and make it a heap before inserting.


template <class Container>
const typename Container::value_type& heap_get_min(const Container& heap){
    if (heap.size() > 1){
        return heap.at(1);
    }
    else{
        throw std::invalid_argument("No elements in heap. ");
    }
} //return the “minimum” value (whichever value is at the root of the heap) in the specified heap (which is passed by constant reference to indicate that this function does not modify the container).  Throw std::invalid_argument if heap is empty.


template <class Container, class Compare=std::less<typename Container::value_type> >
void heap_delete_min(Container* heap, Compare compare = std::less<typename Container::value_type>{}){
    if (heap->size() < 2){
        throw std::invalid_argument("Empty Heap. ");
    }
    size_t i = 1;
    size_t child = 2;
    (*heap)[i] = heap->at(heap->size() - 1);
    heap->pop_back();

    while (heap->size()-1 >= child){
        if (child != heap->size()-1 && compare(heap->at(child+1), heap->at(child))){
            child += 1;
        }

        if ( compare(heap->at(child) , heap->at(i))){
            typename Container::value_type temp = heap->at(i);
            (*heap)[i] = heap->at(child);
            (*heap)[child] = temp;
            i = child;
            child *= 2;
        }
        else{
            return;
        }
        
    }

} //remove the “minimum” value (whichever value is at the root of the heap) in the specified heap (passed by pointer value to indicate that this function modifies the container, which is assumed to already be in heap order with first element in index 1) using the specified comparator (default std::less for a min heap).   Throw std::invalid_argument if heap is empty.


#endif  // HEAP_H