#include <iostream>
#include "collection.h"

using namespace std;

int main(){
    
   Collection<int> collection;
   
    if (collection.is_empty()){
        cout<<"Empty: good"<<endl;
    }
    collection.insert(8);
    collection.insert(6);
    collection.insert(7);
    collection.insert(5);
    collection.insert(3);
    collection.insert(0);
    collection.insert(9);

    Collection<int> poopy;
    
    poopy = collection;
    poopy.print_e();
    
    cout<<"size: "<<poopy.size()<<endl;
    cout<<"size: "<<collection.size()<<endl;

    bool a = collection.contains(0);
    bool b = collection.contains(1);
    bool c = collection.contains(2);
    bool d = collection.contains(3);
    bool e = collection.contains(4);
    bool f = collection.contains(5);
    bool g = collection.contains(6);
    bool h = collection.contains(7);
    bool i = collection.contains(8);
    bool j = collection.contains(9);
    
    collection.print_e();
    cout<<endl;

    if (a == true && i == true && b == false){
        cout<<"shallow check is good"<<endl;
    }


    collection.remove(8);
    
    a = collection.contains(0);
    b = collection.contains(1);
    c = collection.contains(2);
    d = collection.contains(3);
    e = collection.contains(4);
    f = collection.contains(5);
    g = collection.contains(6);
    h = collection.contains(7);
    i = collection.contains(8);
    j = collection.contains(9);

    if (i == true){
        cout<<"8 is still inside"<<endl;
    }
    
    if (g == false){
        cout<<"6 error"<<endl;
    }
    if (h == false){
        cout<<"9 error"<<endl;
    }

    cout<<"size: "<<collection.size()<<endl;
    collection.print_e();

    collection.make_empty();

    collection.print_e();

    if (collection.is_empty()){
        cout<<"Empty: good"<<endl;
    }

    Collection<double> uno;
    uno.insert(2.2);
    cout<<uno.size()<<endl;
    bool t = uno.is_empty();
    uno.make_empty();
    
    return 0;
}