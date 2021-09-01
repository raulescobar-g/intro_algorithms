#include "hashtable_open_addressing.h"
#include <chrono>
using namespace std::chrono;



int main(){

    HashTable<int> table;
    table.insert(0);
    table.insert(11);
    table.insert(22);
    table.insert(33);
    table.insert(44);
    table.insert(55);
    table.remove(0);
    table.insert(23);
    table.insert(9);
    table.insert(10);
    table.insert(34);
    table.insert(21);
    table.insert(55);
    table.print_table();

    









    return 0;
}






























