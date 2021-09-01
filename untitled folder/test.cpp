#include <iostream>


long fib ( int n )
{
    
    if ( n <= 1 )
        return 1;
    else
        return fib(n-1) + fib( n-2 ); 
}



int main(){
    long a = fib(4);

}
