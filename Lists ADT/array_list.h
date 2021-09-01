#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdexcept>

template <class T>
class ArrayList{
    private:
        T * container = nullptr;
        size_t p_size;
        size_t capacity;

    public:
        ArrayList();
        explicit ArrayList(size_t a);
        ArrayList(const ArrayList<T>& a);
        ~ArrayList();
        ArrayList& operator=(const ArrayList<T>& a);
        size_t size();
        T& operator[](size_t a);
        void insert(size_t a, const T& b);
        void remove(size_t index);
};

template <class T>
ArrayList<T>::ArrayList():p_size(0),capacity(2){
    container = new T[2];
}

template <class T>
ArrayList<T>::ArrayList(size_t a):p_size(0),capacity(a){
    container = new T[a];
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& a){
    this->p_size = a.p_size;
    this->capacity = a.capacity;
    this->container = new T[this->capacity];
    for (size_t i = 0; i < this->p_size; ++i){
        this->container[i] = a.container[i];
    }
}

template <class T>
ArrayList<T>::~ArrayList(){
    if (container != nullptr){
        delete[] container;
    }
}

template <class T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& a){
    if (this != &a){
        this->p_size = a.p_size;
        this->capacity = a.capacity;
        if (this->container != nullptr){
            delete[] this->container;
        }
        this->container = new T[this->capacity];
        for (size_t i = 0; i < this->p_size; ++i){
            this->container[i] = a.container[i];
        }
    }
    return *this;
}
 
template <class T>
size_t ArrayList<T>::size(){
    return p_size;
}

template <class T>
T& ArrayList<T>::operator[](size_t a){
    if (a >= p_size){
        throw std::out_of_range("Out of bounds");
    }
    return container[a];
}

template <class T>
void ArrayList<T>::insert(size_t a, const T& b){
    if (a <= p_size){
        if (p_size + 1 <= capacity){
            for(size_t i = p_size; i > a;--i){
                container[i] = container[i-1];
            }
            container[a] = b;                
        }
        else{
            T * temp = new T[capacity*2];
            capacity *= 2;
            for (size_t i = 0; i < a; ++i){
                temp[i] = container[i];
            }
            temp[a] = b;
            for (size_t i = a+1; i < p_size+1;++i){
                temp[i] = container[i-1];
            }
            delete[] container;
            container = temp;
        }
        ++p_size;
    }
    else{
        throw std::out_of_range("Out of Bounds access");
    }
}

template <class T>
void ArrayList<T>::remove(size_t index){
    if ((p_size >= 1) && (index < p_size) && (index >= 0)){
        for (size_t i = index; i < p_size-1;++i){
            container[i] = container[i+1];
        }
        p_size -= 1;
    }
    else{
        throw std::out_of_range("Invalid input");
    }
}



#endif