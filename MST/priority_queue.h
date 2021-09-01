#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "heap.h"

#include <vector>
#include <sstream>


template <class Comparable, class Container=std::vector<Comparable>, class Compare=std::less<typename Container::value_type> >
class PriorityQueue {
    private:
        Compare compare;
        Container container;

    public:
        PriorityQueue(); //makes an empty priority queue using the default container (std::vector) and default comparator (std::less).
        explicit PriorityQueue(const Compare&); // makes an empty priority queue using the default container (std::vector) and specified comparator.
        explicit PriorityQueue(const Container&); // makes a priority queue using the specified container (which may not be empty and is not a heap) and default comparator (std::less).
        PriorityQueue(const Compare&, const Container&); // makes a priority queue using the specified container (which may not be empty and is not a heap) and the specified comparator.
    
        typename Container::const_reference top() const; //return the top of this priority queue. Throw std::invalid argument if the queue is empty.


        bool empty() const; //returns true if this priority queue is empty
        size_t size() const; // returns the number of values in this priority queue


        void make_empty(); //remove all values from this priority queue
        void push(const typename Container::value_type&); // insert the given lvalue reference into this priority queue
        void pop(); // remove the top of this priority queue.  Does not throw any exceptions.


        void print_queue(std::ostream& = std::cout) const; // prints “<empty>\n” if this priority queue is empty. E.g. 1, 2, 4, 3, 6, 5, 11

    
};


template <class Comparable, class Container, class Compare>
PriorityQueue<Comparable, Container,Compare>::PriorityQueue():container(){
    container.insert(container.begin(),typename Container::value_type{});
}


template <class Comparable, class Container, class Compare>
PriorityQueue<Comparable, Container,Compare>::PriorityQueue(const Compare& cmp): container(), compare(cmp){
    container.insert(container.begin(), typename Container::value_type{});
}


template <class Comparable, class Container, class Compare>
PriorityQueue<Comparable, Container,Compare>::PriorityQueue(const Container& contain): container(contain){
    heapify(&container);
}

template <class Comparable, class Container, class Compare>
typename Container::const_reference PriorityQueue<Comparable, Container,Compare>::top() const{
    if (empty()){
        throw std::invalid_argument("Priority Queue empty. ");
    }
    return container.at(1);
} //return the top of this priority queue. Throw std::invalid argument if the queue is empty.


template <class Comparable, class Container, class Compare>
PriorityQueue<Comparable, Container,Compare>::PriorityQueue(const Compare& cmp, const Container& contain): container(contain), compare(cmp){
    heapify(&container);
}


template <class Comparable, class Container, class Compare>
bool PriorityQueue<Comparable, Container,Compare>::empty() const{
    if (container.size() <= 1){
        return true;
    }
    return false;
}


template <class Comparable, class Container, class Compare>
size_t PriorityQueue<Comparable, Container,Compare>::size() const{
    return container.size()-1;
}


template <class Comparable, class Container, class Compare>
void PriorityQueue<Comparable, Container,Compare>::make_empty(){
    container.resize(1);
}


template <class Comparable, class Container, class Compare>
void PriorityQueue<Comparable, Container,Compare>::push(const typename Container::value_type& value){
    heap_insert(&container, value, compare);
}


template <class Comparable, class Container, class Compare>
void PriorityQueue<Comparable, Container,Compare>::pop(){
    try{
        heap_delete_min(&container, compare);
    }
    catch (std::invalid_argument(e)){
        return;
    }
}


template <class Comparable, class Container, class Compare>
void PriorityQueue<Comparable, Container,Compare>::print_queue(std::ostream& out) const{
    std::stringstream ss;
    if (empty()){
        out<<"<empty>\n";
        return;
    }
    for (size_t i = 1; i < container.size()-1; ++i){
        ss << container[i] << ", ";
    }
    ss << container[container.size()-1]<<std::endl;

    out << ss.str();
}



#endif  // PRIORITY_QUEUE_H