#include "hashtable_separate_chaining.h"


int main(){
    HashTable<int> table;
    
    for (int i = 0; i < 100; ++i){
        table.insert(i);
    }
    table.print_table();
    table.rehash(20);
    table.print_table();
    
    
   

    return 0;
}


