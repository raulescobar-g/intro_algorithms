#ifndef QUEUE_H
#define QUEUE_H
#include "doubly_linked_list.h"
#include <stdexcept>


template <typename Object>
class Queue {
    private:
        DoublyLinkedList<Object> list;
        size_t count;
    public:
        Queue();
        Queue(const Queue&);
        ~Queue();
        Queue& operator=(const Queue&);
        void enqueue(const Object&);
        Object dequeue();//throw std::out_of_range if the queue is empty.
        Object& front();//throw std::out_of_range if the queue is empty.
        size_t size1() const;
};

template <typename Object>
Queue<Object>::Queue():list(),count(0){}

template <typename Object>
Queue<Object>::Queue(const Queue& copy):list(copy.list),count(copy.count){}

template <typename Object>
Queue<Object>::~Queue(){}

template <typename Object>
Queue<Object>& Queue<Object>::operator=(const Queue& copy){
    this->count = copy.count;
    this->list = copy.list;
    return *this;
}

template <typename Object>
void Queue<Object>::enqueue(const Object& data){
    list.insert(list.size(),data);
    count += 1;
}

template <typename Object>
Object Queue<Object>::dequeue(){
    Object a = list[0];
    list.remove(0);
    count-=1;
    return a;
}

template <typename Object>
Object& Queue<Object>::front(){
    return list[0];
}

template <typename Object>
size_t Queue<Object>::size1()const{
    return count;
}

#endif  // QUEUE_H
