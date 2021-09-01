#include "hashtable_separate_chaining.h"

int main() {
    HashTable<int> table;
    int test_limit = 10000;

    if (table.max_load_factor() != 1){
        std::cout<<"Error with max load factor"<<std::endl;
    }

    for (int i = 0; i < test_limit; ++i){
        table.insert(i);
    }
    for (int i = 0; i < test_limit; ++i){
        table.insert(i);
    }
    for (int i = 0; i < test_limit/2; ++i){
        table.remove(i);
    }
    for (int i = 0; i < test_limit/2; ++i){
        table.insert(i);
    }

    HashTable<int> copy(table);

    if (copy.is_empty()){
        std::cout<<"copy unsuccessful" <<std::endl;
    }

    for (int i = 0; i < test_limit; ++i){
        if (!table.contains(i)){
            std::cout<<"Mising some inserts. "<<std::endl;
        }
        if (table.bucket(i) != copy.bucket(i)){
            std::cout<<"copy unsuccessful" <<std::endl;
        }
    }
    for (int i = 0; i < test_limit; ++i){
        table.remove(i);
    }
    for (int i = 0; i < test_limit; ++i){
        table.remove(i);
    }
    for (int i = 0; i < test_limit; ++i){
        if (table.contains(i)){
            std::cout<<"Mising some removes. "<<std::endl;
        }
    }
    if (copy.is_empty()){
        std::cout<<"copy unsuccessful" <<std::endl;
    }
    copy = table;
    if (!copy.is_empty()){
        std::cout<<"copy unsuccessful" <<std::endl;
    }
    try{
        table.bucket_size(-1);
    }
    catch (std::out_of_range(e)){
        std::cout<<"ERROR : "<<e.what()<<std::endl;
    }
    try{
        table.bucket_size(100000000000);
    }
    catch (std::out_of_range(e)){
        std::cout<<"ERROR : "<<e.what()<<std::endl;
    }
    try{
        table.max_load_factor(0);
    }
    catch (std::invalid_argument(e)){
        std::cout<<"ERROR : "<<e.what()<<std::endl;
    }
    try{
        table.max_load_factor(-3);
    }
    catch (std::invalid_argument(e)){
        std::cout<<"ERROR : "<<e.what()<<std::endl;
    }
    HashTable<std::string> table1;
    std::cout << "initial size is " << table1.size() << std::endl;
    std::cout << "initial bucket count is " << table1.bucket_count() << std::endl;
    std::cout << "initial load factor is " << table1.load_factor() << std::endl;
    std::cout << "initial max load factor is " << table1.max_load_factor() << std::endl;

    std::string array[] = {"hello","goodbye","raul","escobar","today","tomorrow", "okay","no","whenever","csce","221","twotwentyone","red","black","trees","hash","browns","separate","table","tests","test","test","testing","duplicate","made for ","s p a c e ","jokes","writing","an","essay","of","strings"};
    for (int i = 0; i < 20; ++i){
        table1.insert(array[i]);
        if (table1.size() != i+1){
            std::cout<<"error with the sizing"<<std::endl;
        }
    }

    table1.max_load_factor(2);
    
    for (int i = 20; i < 32; ++i){
        table1.insert(array[i]);
        if (table1.size() != i){
            std::cout<<"error with the sizing1"<<std::endl;
        }
    }
    size_t buckets = table1.bucket_count();
    std::cout<<buckets<<std::endl;
    table1.print_table();
    
    table1.max_load_factor(0.5);
    std::cout<<"Load factor :"<<table1.load_factor()<<std::endl;
    table1.print_table();
    if (table1.max_load_factor() != 0.5){
        std::cout<<"Error with the max_load_factor"<<std::endl;
    }
    
    for (int i = 0; i < 32; ++i){
        if (!table1.contains(array[i])){
            std::cout<<"Error missing some inserts: "<<array[i]<<std::endl;
        }
    }
    for (int i = 0; i < 32; ++i){
        table1.bucket_size(i);
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
    table1.max_load_factor(1);

    std::cout<<"Ritcheys example test cases: "<<std::endl;

    std::cout << "make an empty hash table with 11 buckets for strings" << std::endl;
    HashTable<std::string> table2(11);

    std::cout << "initial size is " << table2.size() << std::endl;
    std::cout << "initial bucket count is " << table2.bucket_count() << std::endl;
    std::cout << "initial load factor is " << table2.load_factor() << std::endl;
    std::cout << "initial max load factor is " << table2.max_load_factor() << std::endl;

    std::cout << "insert several strings" << std::endl;   
    table2.insert("And them who hold High Places");
    table2.insert("Must be the ones to start");
    table2.insert("To mold a new Reality");
    table2.insert("Closer to the Heart");
    table2.insert("The Blacksmith and the Artist");
    table2.insert("Reflect it in their Art");
    table2.insert("Forge their Creativity");
    table2.insert("Closer to the Heart");
    table2.insert("Philosophers and Plowmen");
    table2.insert("Each must know their Part");
    table2.insert("To sow a new Mentality");
    table2.insert("Closer to the Heart");
    table2.insert("You can be the Captain");
    table2.insert("I will draw the Chart");
    table2.insert("Sailing into Destiny");
    table2.insert("Closer to the Heart");

    std::cout << "size is " << table2.size() << std::endl;
    std::cout << "bucket count is " << table2.bucket_count() << std::endl;
    std::cout << "load factor is " << table2.load_factor() << std::endl;
    std::cout << "max load factor is " << table2.max_load_factor() << std::endl;


    {
  	std::cout << "print the table" << std::endl;
  	std::stringstream ss;
  	table2.print_table(ss);
  	std::cout << ss.str() << std::endl;
    }

    std::cout << "remove \"Philosophers and Plowmen\"" << std::endl;
    table2.remove("Philosophers and Plowmen");
    std::cout << "remove \"Each must know their Part\"" << std::endl;

    table2.remove("Each must know their Part");

    std::cout << "size is " << table2.size() << std::endl;
    std::cout << "bucket count is " << table2.bucket_count() << std::endl;
    std::cout << "load factor is " << table2.load_factor() << std::endl;
    std::cout << "max load factor is " << table2.max_load_factor() << std::endl;

    {
  	std::cout << "print the table" << std::endl;
  	std::stringstream ss;
  	table2.print_table(ss);
  	std::cout << ss.str() << std::endl;
    }

    std::cout << "set max load factor to 2" << std::endl;
    table2.max_load_factor(2);
    std::cout << "rehash the table to size 7" << std::endl;
    table2.rehash(7);

    std::cout << "size is " << table2.size() << std::endl;
    std::cout << "bucket count is " << table2.bucket_count() << std::endl;
    std::cout << "load factor is " << table2.load_factor() << std::endl;
    std::cout << "max load factor is " << table2.max_load_factor() << std::endl;

    {
  	std::cout << "print the table" << std::endl;
  	std::stringstream ss;
  	table2.print_table(ss);
  	std::cout << ss.str() << std::endl;
    }

    std::cout << "find \"The Blacksmith and the Artist\"" << std::endl;
    size_t index = table2.bucket("The Blacksmith and the Artist");
    std::cout << " ==> bucket " << index << std::endl;
    std::cout << "     which has " << table2.bucket_size(index) << " elements" << std::endl;

    std::cout << "make the table empty" << std::endl;
    table2.make_empty();

    std::cout << "size is " << table2.size() << std::endl;
    std::cout << "bucket count is " << table2.bucket_count() << std::endl;
    std::cout << "load factor is " << table2.load_factor() << std::endl;
    std::cout << "max load factor is " << table2.max_load_factor() << std::endl;

    {
  	std::cout << "print the table" << std::endl;
  	std::stringstream ss;
  	table2.print_table(ss);
  	std::cout << ss.str() << std::endl;
    }




    return 0;
}
