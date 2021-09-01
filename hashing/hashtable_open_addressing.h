#ifndef HASHTABLE_OPEN_ADDRESSING_H
#define HASHTABLE_OPEN_ADDRESSING_H

#include <iostream>
#include <functional>
#include <vector>
#include <sstream>
#include <stdexcept>
using std::vector;

template <class Key, class Hash=std::hash<Key>>
class HashTable {
    public:
        HashTable(); //makes an empty table with 11 buckets
        explicit HashTable(size_t); //makes an empty table with the specified number of buckets
        
        bool is_empty() const; //returns true if the table is empty
        size_t size() const; //returns the number of values in the table
        size_t table_size() const; //return the number of cells in the table
        void make_empty(); //remove all values from the table
        size_t position(const Key&) const; //return the index of the cell that would contain the specified value.  This method handles collision resolution.
        bool contains(const Key&) const; //returns Boolean true if the specified value is in the table
        bool insert(const Key&); //insert the given lvalue reference into the table, rehashing if the maximum load factor is exceeded, return true if insert was successful (false if item already exists)
        size_t remove(const Key&); //remove the specified value from the table, return number of elements removed (0 or 1).
        void rehash(size_t); //set the number of buckets to the specified value and rehash the table if the total number of buckets has changed. If the new number of buckets would cause the load factor to exceed the maximum load factor, then the new number of buckets is at least size() / max_load_factor().
        void print_table(std::ostream& = std::cout) const; //pretty print the table.  Required to exist and produce reasonable output, the empty table should print “<empty>\n”, but the format of the output is not graded

    private:
        enum EntryType {ACTIVE, EMPTY, DELETED};
        struct HashEntry{
            Key element;
            EntryType info;
            HashEntry( const Key& e = Key{ }, EntryType i = EMPTY ) : element{ e }, info{ i } { }
        };
        
        vector<HashEntry> table;
        size_t siz;
        size_t actual;
        float max_load_factor;
        size_t capacity;
        size_t get_next_prime(size_t prev_size);
        bool IsPrime(int number);
};

template <class Key, class Hash>
HashTable<Key,Hash>::HashTable(): siz(0), actual(0) ,max_load_factor(0.5), capacity(11){
    table.resize(11);
    for (auto & entry : table){
        entry.info = EMPTY;
    }
}

template <class Key, class Hash>
HashTable<Key,Hash>::HashTable(size_t pre_sized): siz(0), actual(0), max_load_factor(0.5), capacity(pre_sized) {
    table.resize(pre_sized);
    for (auto & entry : table){
        entry.info = EMPTY;
    }
}

template <class Key, class Hash>
bool HashTable<Key,Hash>::is_empty() const{
    if (siz == 0){
        return true;
    }
    return false;
}

template <class Key, class Hash>
size_t HashTable<Key,Hash>::size() const{
    return siz;
}

template <class Key, class Hash>
size_t HashTable<Key,Hash>::table_size() const{
    return capacity;
}

template <class Key, class Hash>
void HashTable<Key,Hash>::make_empty(){
    siz = 0;
    for(auto & entry : table){
        entry.info = EMPTY;
    }
}

template <class Key, class Hash>
bool HashTable<Key,Hash>::insert(const Key& data){
    size_t hash_value = position(data);
    if (table[hash_value].info == ACTIVE){
        return false;
    }
    else{
        if ((float)(actual+1)/capacity > max_load_factor){
            size_t prime = get_next_prime(capacity*2);
            rehash(prime);
            insert(data);
        }
        else{
            table[hash_value].info = ACTIVE;
            table[hash_value].element = data;
            siz +=1;
            actual += 1;
            return true;
        }
    }
}

template <class Key, class Hash>
size_t HashTable<Key,Hash>::get_next_prime(size_t prev_size){
    while (!IsPrime(++prev_size)){ }
    return prev_size;
}

template <class Key, class Hash>
bool HashTable<Key,Hash>::IsPrime(int number){
    if (number % 2 == 0 || number % 3 == 0)
        return false;
    int divisor = 6;
    while ((divisor-1) * (divisor-1) <= number){
        if (number % (divisor - 1) == 0)
            return false;
        if (number % (divisor + 1) == 0)
            return false;
        divisor += 6;
    }
    return true;
}

template <class Key, class Hash>
size_t HashTable<Key,Hash>::remove(const Key& data){
    size_t hash_value = position(data);
    
    if (table[hash_value].info != ACTIVE){
        return 0;
    }
    else{
        table[hash_value].info = DELETED;
        siz -= 1;
        return 1;
    }
    
}

template <class Key, class Hash>
bool HashTable<Key,Hash>::contains(const Key& data) const{
    size_t hash_value = position(data);
    return table[hash_value].info == ACTIVE;
}

template <class Key, class Hash>
void HashTable<Key,Hash>::rehash(size_t new_size){
    capacity = new_size;
    vector<HashEntry> old = table;

    table.resize(new_size);
    for(auto & entry : table){
        entry.info = EMPTY;
    }

    size_t hash_value;

    for (auto & entry : old){
        if (entry.info == ACTIVE){
            hash_value = position(entry.element);
            table[hash_value].info = ACTIVE;
            table[hash_value].element = entry.element;
        }
        else{
            entry.info = EMPTY;
        }
    }
    actual = siz;
}

template <class Key, class Hash>
void HashTable<Key,Hash>::print_table(std::ostream& out) const{
    int count = 0;
    if (is_empty() == true){
        out<< "<empty>\n";
        return;
    }
    for( auto & linked: table){
        out<<count<<": ";
        if (linked.info == ACTIVE){
            out<<linked.element;
        }
        out<<std::endl;
        count += 1;
    }
}

template <class Key, class Hash>
size_t HashTable<Key,Hash>::position(const Key& data) const{
    //followed template from the book on quadratic probing but to mitigate the fact that most of the work came from the book i will
    //explain this function to show that i do understand it, annd it is not blind copying
    
    //most of heavy lifting comes from the while loop check

    //set offset used later to increase the hash address by an odd number which is equivalent to increaseing by a square... sum(2n+1) == n^2
    //then we get the address in the line under
    int offset = 1;
    size_t hash_value = Hash{}(data) % capacity;

    //while loop checks that address is not empty and that the data != element
    // if it is empty, then we can insert the value into that bucket and we can skip the while loop
    //if it is active or deleted, we check that it has a different value,
    //if it has the same value, then we can skip the while loop because we found where the element belongs, 
    //if it does not have the same value, we increase the hash address by an oddnumber and check again
    while(table[hash_value].info != EMPTY && table[hash_value].element != data){
        //increase by odd number
        hash_value += offset; 
        offset += 2;

        //mod the new address
        hash_value = hash_value % capacity;
    }
    return hash_value;
}




#endif  // HASHTABLE_OPEN_ADDRESSING_H