#include "hashtable_open_addressing.h"

int main() {
    HashTable<int> table2;
    table2 = table2;
    int test_limit = 1000;

    for (int i = 0; i < test_limit; ++i){
        table2.insert(i);
    }
    for (int i = 0; i < test_limit; ++i){
        table2.insert(i);
    }
    HashTable<int> copy(table2);

    if (copy.is_empty()){
        std::cout<<"copy unsuccessful" <<std::endl;
    }

    for (int i = 0; i < test_limit; ++i){
        if (!table2.contains(i)){
            std::cout<<"Mising some inserts. "<<std::endl;
        }
    }
    for (int i = 0; i < test_limit; ++i){
        table2.remove(i);
    }
    for (int i = 0; i < test_limit; ++i){
        table2.remove(i);
    }
    for (int i = 0; i < test_limit; ++i){
        if (table2.contains(i)){
            std::cout<<"Mising some removes. "<<std::endl;
        }
    }
    if (copy.is_empty()){
        std::cout<<"copy unsuccessful" <<std::endl;
    }
    copy = table2;
    if (!copy.is_empty()){
        std::cout<<"copy unsuccessful" <<std::endl;
    }
    
    HashTable<std::string> table1;
    std::cout << "initial size is " << table1.size() << std::endl;

    std::string array[] = {"hello","goodbye","raul","escobar","today","tomorrow", "okay","no","whenever","csce","221","twotwentyone","red","black","trees","hash","browns","separate","table","tests","test","test","testing","duplicate","made for ","s p a c e ","jokes","writing","an","essay","of","strings"};
    for (int i = 0; i < 20; ++i){
        table1.insert(array[i]);
        if (table1.size() != i+1){
            std::cout<<"error with the sizing"<<std::endl;
        }
    }
    
    for (int i = 20; i < 32; ++i){
        table1.insert(array[i]);
        if (table1.size() != i){
            std::cout<<"error with the sizing1"<<std::endl;
        }
    }
    table1.print_table();

    for (int i = 0; i < 32; ++i){
        if (!table1.contains(array[i])){
            std::cout<<"Error missing some inserts: "<<array[i]<<std::endl;
        }
    }
    
    for (int i = 0; i < 10; ++i){
        table1.remove(array[i]);
        if (table1.size() != 32-2-i){
            std::cout<<"error with the sizing2"<<std::endl;
        }
    }
    for (int i = 0; i < 10; ++i){
        if (table1.contains(array[i])){
            std::cout<<"error missing some removes"<<std::endl;
        } 
    }

    std::cout<<"Ritcheys example test cases: "<<std::endl;
    std::cout << "make an empty hash table with 11 buckets for strings" << std::endl;
    HashTable<std::string> table(11);

    std::cout << "initial size is " << table.size() << std::endl;
    std::cout << "initial table size is " << table.table_size() << std::endl;

    std::cout << "insert several strings" << std::endl;   
    table.insert("And them who hold High Places");
    table.insert("Must be the ones to start");
    table.insert("To mold a new Reality");
    table.insert("Closer to the Heart");
    table.insert("The Blacksmith and the Artist");
    table.insert("Reflect it in their Art");
    table.insert("Forge their Creativity");
    table.insert("Closer to the Heart");
    table.insert("Philosophers and Plowmen");
    table.insert("Each must know their Part");
    table.insert("To sow a new Mentality");
    table.insert("Closer to the Heart");
    table.insert("You can be the Captain");
    table.insert("I will draw the Chart");
    table.insert("Sailing into Destiny");
    table.insert("Closer to the Heart");

    std::cout << "size is " << table.size() << std::endl;
    std::cout << "table size is " << table.table_size() << std::endl;

    {
    std::cout << "print the table" << std::endl;
    std::stringstream ss;
    table.print_table(ss);
    std::cout << ss.str() << std::endl;
    }

    std::cout << "remove \"Philosophers and Plowmen\"" << std::endl;
    table.remove("Philosophers and Plowmen");
    std::cout << "remove \"Each must know their Part\"" << std::endl;
    table.remove("Each must know their Part");

    std::cout << "size is " << table.size() << std::endl;
    std::cout << "table size is " << table.table_size() << std::endl;

    {
    std::cout << "print the table" << std::endl;
    std::stringstream ss;
    table.print_table(ss);
    std::cout << ss.str() << std::endl;
    }

    std::cout << "find \"The Blacksmith and the Artist\"" << std::endl;
    size_t index = table.position("The Blacksmith and the Artist");
    std::cout << " ==> cell " << index << std::endl;

    std::cout << "make the table empty" << std::endl;
    table.make_empty();

    std::cout << "size is " << table.size() << std::endl;
    std::cout << "table size is " << table.table_size() << std::endl;

    {
    std::cout << "print the table" << std::endl;
    std::stringstream ss;
    table.print_table(ss);
    std::cout << ss.str() << std::endl;
    }
    
    return 0;
}