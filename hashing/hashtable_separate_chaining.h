#ifndef HASHTABLE_SEPARATE_CHAINING_H
#define HASHTABLE_SEPARATE_CHAINING_H

#include <iostream>
#include <list>
#include <functional>
#include <vector>
#include <sstream>
#include <stdexcept>
using std::list;
using std::vector;

template <class Key, class Hash = std::hash<Key> >
class HashTable{
    public:
        HashTable(); //makes an empty table with 11 buckets
        explicit HashTable(size_t); //makes an empty table with the specified number of buckets
        HashTable(const HashTable&); //constructs a copy of the given table
        ~HashTable(); //destructs this table
        HashTable& operator=(const HashTable&); //assigns a copy of the given table
        bool is_empty() const; //returns true if the table is empty
        size_t size() const; //returns the number of values in the table
        void make_empty(); //remove all values from the table
        bool insert(const Key&); //insert the given lvalue reference into the table, rehashing if the maximum load factor is exceeded, return true if insert was successful (false if item already exists)
        size_t remove(const Key&); //remove the specified value from the table, return number of elements removed (0 or 1).
        bool contains(const Key&) const; //returns Boolean true if the specified value is in the table
        void rehash(size_t); //set the number of buckets to the specified value and rehash the table if the total number of buckets has changed. If the new number of buckets would cause the load factor to exceed the maximum load factor, then the new number of buckets is at least size() / max_load_factor().
        size_t bucket_count() const; //return the number of buckets in the table
        size_t bucket_size(size_t) const; //return the number of values in the specified bucket; throw std::out_of_range if the bucket index is out of bounds of the table.
        size_t bucket(const Key&) const; //return the index of the bucket that contains the specified value (or would contain it, if it existed)
        float load_factor() const; //return the current load factor of the table
        float max_load_factor() const; //return the current maximum load factor of the table 
        void max_load_factor(float); //set the maximum load factor of the table, forces a rehash if the new maximum is less than the current load factor, throws std::invalid_argument if the input is invalid 
        void print_table(std::ostream& = std::cout) const; //pretty print the table.  Required to exist and produce reasonable output, the empty table should print “<empty>\n”, but the format of the output is not graded
        size_t get_next_prime(size_t prev_size);
        bool IsPrime(int number);

    private: 
        size_t siz;
        size_t buckets;
        float max_load_factor1;
        vector<list<Key> > father_bucket;
        
};

template <class Key, class Hash>
HashTable<Key,Hash>::HashTable(): siz(0),buckets(11), max_load_factor1(1){
    father_bucket.resize(11);
    //std::fill(father_bucket.begin(),father_bucket.end(),list<Key> );
}

template <class Key, class Hash>
HashTable<Key,Hash>::HashTable(size_t pre_sized): siz(0),buckets(pre_sized),max_load_factor1(1) {
    father_bucket.resize(pre_sized);
}

template <class Key, class Hash>
HashTable<Key,Hash>::HashTable(const HashTable<Key,Hash>& copy): siz(copy.siz),buckets(copy.buckets), max_load_factor1(copy.max_load_factor1) {
    father_bucket.resize(copy.buckets);
    for (int i = 0; i < copy.buckets ; ++i){
        father_bucket[i] = copy.father_bucket[i];
    }
}

template <class Key, class Hash>
HashTable<Key,Hash>::~HashTable(){}

template <class Key, class Hash>
HashTable<Key,Hash>& HashTable<Key,Hash>::operator=(const HashTable<Key,Hash>& copy) {
    if (this != &copy){
        siz = copy.siz;
        buckets = copy.buckets;
        max_load_factor1 = copy.max_load_factor1;
        father_bucket.resize(copy.buckets);
        for (int i = 0; i < copy.buckets ; ++i){
            father_bucket[i] = copy.father_bucket[i];
        }
    }
    return *this;
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
void HashTable<Key,Hash>::make_empty(){
    for(auto & linked : father_bucket){
        linked.clear();
    }
    siz = 0;
}

template <class Key, class Hash>
bool HashTable<Key,Hash>::insert(const Key& data){
    size_t hash_value = Hash{}(data) % buckets;
    auto iter = (father_bucket[hash_value]).begin();
    for ( ;iter != (father_bucket[hash_value]).end(); ++iter){
        if (*iter == data){
            return false;
        }
    }
    (father_bucket[hash_value]).push_back(data);

    if ((float)(++siz)/buckets > max_load_factor1) {
        //std::cout<<"Rehashing..."<<std::endl;
        rehash(get_next_prime(buckets*2)); //needs to update buckets
    }
    return true;
}

template <class Key, class Hash>
size_t HashTable<Key,Hash>::get_next_prime(size_t prev_size){
    while (!IsPrime(++prev_size)){ }
    return prev_size;
}

template <class Key, class Hash>
size_t HashTable<Key,Hash>::remove(const Key& data){
    size_t hash_value = Hash{}(data);
    hash_value = hash_value % buckets;
    auto iter = (father_bucket[hash_value]).begin();
    for ( ;iter != (father_bucket[hash_value]).end(); ++iter){
        if (*iter == data){
            (father_bucket[hash_value]).erase(iter);
            siz -= 1;
            return 1;
        }
    }
    return 0;
}

template <class Key, class Hash>
bool HashTable<Key,Hash>::contains(const Key& data) const{
    size_t hash_value = Hash{}(data)% buckets;
    auto iter = (father_bucket[hash_value]).begin();
    for ( ;iter != (father_bucket[hash_value]).end(); ++iter){
        if (*iter == data){
            return true;
        }
    }
    return false;
}

template <class Key, class Hash>
void HashTable<Key,Hash>::rehash(size_t new_size){
    if (new_size != buckets){
        if (((float)siz/new_size) > max_load_factor1){
            new_size = get_next_prime((size_t)(siz / max_load_factor1));
        }
        buckets = new_size;
        vector<list<Key> > rehashed = father_bucket;
        father_bucket.resize(new_size);
        make_empty();

        for(auto & linked: rehashed){
            for(auto & x : linked) {
                size_t hash_value = Hash{}(x) % buckets;
                (father_bucket[hash_value]).push_back(x);
                siz += 1;
                //consider since this is a public function someone calls it making it smaller and u dont rehash cuz u didnt use insert ,,,, check cases in mimir
            }
        }
    }
}

template <class Key, class Hash>
size_t HashTable<Key,Hash>::bucket_count() const{
    return buckets;
}

template <class Key, class Hash>
size_t HashTable<Key,Hash>::bucket_size(size_t index) const{
    if (index >= buckets || index < 0){
        throw std::out_of_range("Tried to access out of bounds. ");
    }
    return (father_bucket[index]).size();
}

template <class Key, class Hash>
size_t HashTable<Key,Hash>::bucket(const Key& value) const{
    return  Hash{}(value) % buckets;
}

template <class Key, class Hash>
float HashTable<Key,Hash>::load_factor() const{
    return siz/(float)buckets;
}

template <class Key, class Hash>
float HashTable<Key,Hash>::max_load_factor() const{
    return max_load_factor1;
}

template <class Key, class Hash>
void HashTable<Key,Hash>::max_load_factor(float new_max){
    if (new_max <= 0){
        throw std::invalid_argument("Invalid argument as new max load factor. ");
    }
    max_load_factor1 = new_max;
    while ((float)siz/buckets > max_load_factor1) {
        //std::cout<<"Rehashing..."<<std::endl;
        size_t prime = get_next_prime(buckets*2);
        rehash(prime); //needs to update buckets
    }
}


template <class Key, class Hash>
void HashTable<Key,Hash>::print_table(std::ostream& out) const{
    int count = 0;
    if (is_empty() == true){
        out<< "<empty>\n";
        return;
    }
    for( auto & linked: father_bucket){
        out<<count<<": ";
        for( auto & x : linked){
            out<< x <<" , ";
        }
        out<<std::endl;
        count += 1;
    }
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


#endif  // HASHTABLE_SEPARATE_CHAINING_H