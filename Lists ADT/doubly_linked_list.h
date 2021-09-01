#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include <stdexcept>

template <class T>
struct Node {
    Node<T> *next;
    Node<T> *prev;
    T data;
    Node(): next(nullptr),prev(nullptr){}
    Node(T data): next(nullptr),prev(nullptr),data(data){}
};          

template <class T>
class DoublyLinkedList{
    private:
        //struct Node;
        size_t p_size;
        Node<T> *head;
        Node<T> *tail;
        
    
    public:
        DoublyLinkedList();
        DoublyLinkedList(const DoublyLinkedList& copy);
        ~DoublyLinkedList();
        DoublyLinkedList<T>& operator=(const DoublyLinkedList& copy);
        T& operator[](size_t pos);
        size_t size() const;
        void insert(size_t pos, const T& data);
        void remove(size_t index);

};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList():p_size(0),head(nullptr),tail(nullptr){}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& copy):p_size(copy.p_size),head(nullptr),tail(nullptr){
    if (copy.size() > 0){
        Node<T> * iter = copy.head;
        this->head = new Node<T>(iter->data);
        this->tail = this->head;
        iter = iter->next;

        Node<T> * lag = this->head;
        Node<T> * future;
        while (iter != nullptr){
            lag->next = new Node<T>(iter->data);
            future = lag->next;
            future->prev = lag;
            lag = lag->next;
            iter = iter->next;
        }
        this->tail = lag;
    }
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList(){
    while (this->head != nullptr){
        Node<T> * iter = this->head;
        head = head->next;
        delete iter;
    }
}

template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& copy){
    if (this != &copy){
        this->p_size = copy.p_size;
        if (copy.head == nullptr){
            head = nullptr;
            tail = nullptr;
        }
        else{
            while (this->head != nullptr){
                Node<T> * iter = this->head;
                head = head->next;
                delete iter;
            }
            Node<T> * iter = copy.head;
            this->head = new Node<T>(iter->data);
            this->tail = this->head;
            iter = iter->next;

            Node<T> * lag = this->head;

            while (iter != nullptr){
                lag->next = new Node<T>(iter->data);
                lag->next->prev = lag;
                lag = lag->next;
                iter = iter->next;
            }
            this->tail = lag;
        }
    }
    return *this;
}

template <class T>
T& DoublyLinkedList<T>::operator[](size_t pos){
    Node<T> * iter = this->head;
    if (pos < p_size){
        for (size_t i = 0; i < pos; ++i){
            iter = iter->next;
        }
        return iter->data;
    }
    else{
        throw std::out_of_range("Position does not exist");
    }
}
    
template <class T>
size_t DoublyLinkedList<T>::size() const{
    return p_size;
}

template <class T>
void DoublyLinkedList<T>::insert(size_t pos, const T& data){
    if (pos <=p_size){
        Node<T> * lag = this->head;
        if (lag == nullptr){
            this->head = new Node<T>(data);
            this->tail = this->head;
            p_size+=1;
        }
        else if (pos == 0){
            Node<T> * obj = new Node<T>(data);
            lag->prev = obj;
            obj->next = lag;
            this->head = obj;
            p_size+=1;
        }
        else if (pos == p_size){
            Node<T> * obj = new Node<T>(data);
            this->tail->next = obj;
            obj->prev = this->tail;
            this->tail = obj;
            p_size+=1;
        }
        else if (pos <= ((p_size)/2)){
            Node<T> * iter = this->head->next;
            for (size_t i = 0; i < pos-1; ++i){
                iter = iter->next;
                lag = lag->next;
            }
            Node<T> * inserted = new Node<T>(data);
            iter->prev = inserted;
            lag->next = inserted;
            inserted->prev = lag;
            inserted->next = iter;
            p_size += 1;
        }
        else if (pos > (p_size/2)){
            lag = this->tail->prev;
            Node<T> * iter = this->tail;
            for (size_t i = p_size-1; i > pos-1; --i){
                iter = iter->prev;
                lag = lag->prev;
            }
            Node<T> * inserted = new Node<T>(data);
            iter->prev = inserted;
            lag->next = inserted;
            inserted->prev = lag;
            inserted->next = iter;
            p_size += 1;
        }
    }
    else{
        throw std::out_of_range("Out of range");
    }        
}

template <class T>
void DoublyLinkedList<T>::remove(size_t index){
    if (index < p_size){
        if (index == 0){
            Node<T> * lag = this->head;
            this->head = this->head->next;
            delete lag;
            p_size -= 1;
        }
        else if (index == p_size-1){
            this->tail = this->tail->prev;
            delete this->tail->next;
            this->tail->next = nullptr;
            p_size -= 1;
        }
        else {
            Node<T> * lag = this->head;
            Node<T> * iter = this->head->next;
            for (size_t i = 0; i < index-1; ++i){
                iter = iter->next;
                lag = lag->next;
            }
            lag->next = iter->next;
            iter->next->prev = lag;
            delete iter;
            p_size -= 1;
        }
    }
    else{
        throw std::out_of_range("Out of range");
    }
}


#endif