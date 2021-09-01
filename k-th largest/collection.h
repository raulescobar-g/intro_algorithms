#ifndef COLLECTION_H
#define COLLECTION_H
#include <iostream>

#include <cstddef>

template <typename Object>
class Collection {
    public:
    Collection();
    Collection(const Collection& coll);
    ~Collection();
    size_t size() const;
    bool is_empty() const;
    void make_empty();
    void insert(const Object& obj);
    void remove(const Object& obj);
    bool contains(const Object& obj) const;
    Collection<Object>& operator=(const Collection& coll);
    void print_e()const;
    
    private:
    size_t count;
    Object *storage;

};

template <typename Object>
void Collection<Object>::print_e()const{
    if (storage != nullptr){
        std::cout<<"["<<storage[0];
        for (size_t i = 1; i < count-1; ++i){
            std::cout<<","<<storage[i];
        }
        std::cout<<","<<storage[count-1]<<"]";
    }
    else{
        std::cout<<"[empty]";
    }
}

template <typename Object>
Collection<Object>::Collection():count(0){
    storage = new Object[0];
}

template <typename Object>
size_t Collection<Object>::size() const{
    return count;
}

template <typename Object>
bool Collection<Object>::is_empty() const{
    if (count == 0){
        return true;
    }
    else {
        return false;
    }
}

template <typename Object>
void Collection<Object>::make_empty(){
    count = 0;
    if (storage != nullptr){
        delete[] storage;
        storage = nullptr;
    }
}

template <typename Object>
void Collection<Object>::insert(const Object& obj){
    count += 1;
    if (storage != nullptr){
        Object *resized = new Object[count];
        for (size_t i = 0;i<count-1;++i){
            resized[i] = storage[i];
        }
        delete[] storage;
        storage = resized;
        storage[count-1] = obj;
    }
    else{
        
        storage = new Object[1];
        storage[0] = obj;
    }
    
}

template <typename Object>
void Collection<Object>::remove(const Object& obj){
    count -= 1;
    bool found = false;

    if (count < 1){
        if (storage != nullptr){
            delete[] storage;
            storage = nullptr;
        }
        count = 0;
    }

    else{
        Object *resized = new Object[count];

        for (size_t i = 0;i < count+1;++i){
            if (found == false){
                if (storage[i] != obj){
                    resized[i] = storage[i];
                }
                else{
                    found = true;
                }
            }
            else {
                resized[i-1] = storage[i];
            }
        }
        delete[] storage;
        storage = resized;
    }

}

template <typename Object>
bool Collection<Object>::contains(const Object& obj) const{
    for (size_t i = 0; i < count;++i){
        if (storage[i] == obj){
            return true;
        }
    }
    return false;
}

template <typename Object>
Collection<Object>& Collection<Object>::operator=(const Collection& coll){
    this->count = coll.count;
    if (this->storage != nullptr){
        delete [] this->storage;
        this->storage = nullptr;
    }
    this->storage = new Object[this->count];
    for (size_t i = 0; i < coll.count;++i){
        this->storage[i] = coll.storage[i];
    } 
    return *this;
}

template <typename Object>
Collection<Object>::~Collection(){
    if (storage != nullptr){
        delete[] storage;
        storage = nullptr;
    } 
}

template <typename Object>
Collection<Object>::Collection(const Collection& coll){
    this->count = coll.count;
    storage = new Object[coll.count];
    for (size_t i = 0; i < coll.count;++i){
        this->storage[i] = coll.storage[i];
    } 
}


#endif  // COLLECTION_H