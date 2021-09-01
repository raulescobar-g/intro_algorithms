#include <iostream>
#include "selection.h"
using namespace std;

int main(){
    
    int array[13] = {1,2,3,4,5,6,5,7,8,9,3,4,5};
    int empty[0] = {};
    int a = select(2,array,13);
    int b = select(5,array,13);
    
    int a1 = select(1,array,13);
    int b1 = select(3,array,13);
    int c1 = select(4,array,13);
    int t = select(1,empty,1);
    cout<<a<<b<<a1<<b1<<c1<<t<<endl;
    
    try{
        int c = select(6,array,5);
        int d = select(6,empty,5);
        int e = select(0,array,5);
        int f = select(1,empty,0);
        
        cout<<"test case normal: "<<d<<endl;
        cout<<"test case normal: "<<e<<endl;
        cout<<"test case normal: "<<f<<endl;
        
    }
    catch (const exception& e){
        cout<<e.what()<<endl;
    }
    

    return 0;
}