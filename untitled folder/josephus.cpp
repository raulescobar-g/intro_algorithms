#include <iostream>
#include <forward_list>
#include <chrono>
using namespace std;
using namespace std::chrono; 

//Works for M = 0
//Function using std::forward_list
int josephus(int N, int M){
    //Define list and populate it from 1 -> N
    //Linear time complexity to populate
    forward_list<int> link(N);
    
    for (int i = N; i >= 0; --i){
        link.push_front(i);
    }
    
    //Iterator to be used
    forward_list<int>::iterator next = link.begin();
    
    //For loop to remove N-1 elements, the last element remaining is the answer.
    //Maybe not a good idea to model the problem exactly as it is executed, but it seemed like a forward...
    //linked list could do the job
    for (int j = 0; j < N-1;++j){ 
        
        //case where M > 0, and iterator must be returned back to the beginning
        //does not work because you have to count how many elements there are between iterator and the end
        //this would cause the solution to be n^2 complexity due to nested for loop
        if (*next + M >= N){
            int b = *next;
            next = link.begin();
            std::advance(next,M-(N-b));
        }

        //case where it just moves M places
        else{
            std::advance(next,M);
        }

        //erase element
        link.erase_after(next);
        
        
    }
    //we delete the zero and output the result
    link.pop_front();
    return link.front();
    
}


//Function but using bare bones arrays and one big delete at the end, verified to work for N=5 M=0,1,2
int josephus_1(int N,int M){
    //define and populate the dynamically allocated array and define the removed variable to keep track of elements "removed"
    int* data = new int[N];
    int removed = 0;
    for (int i = 0; i <= N; ++i){
        data[i] = i+1;
        //for debug purposes
        //cout<<i<<endl;
    }

//iterator and main loop that iterates N-1 times.
    int j = 0;
    while (removed != N-1){
        
        //Checks that next number isnt "deleted" and skips that number if it is
        for (int p = 0; p < M;++p){
            int checker = 1;
            while(data[(j+p+checker)%N] == -1){
                j = (j+1)%N;
                ++checker;
            }

            j = (j+1)%N;
        }
        //for debuging
        //cout<<j+1<<endl;

        //to avoid deleting and reallocating every time which would be costly, the numbers are simply set to -1, and everything is deleted at the end.
        data[j] = -1;
        ++removed;

        //after deleteing we have to move the iterator up one, but we have to check that the next one isnt deleted as well.
        if (data[(j+1)%N] == -1){
            while(data[(j+1)%N] == -1){
                j = (j+1)%N;
            }
            j = (j+1)%N;
        }
        else {
            j = (j+1)%N;
        }
    }

    for (int k = 0; k < N; ++k){
        //cout<<data[k]<<endl;
        if (data[k] != -1){
            int z = data[k];
            delete[] data;
            return z;
        }
    }

    delete[] data;
    return 0;
}

int main(){
    //Checks runtime in milliseconds for the first 15 entries of N with M set to 1.
    for (int i = 2; i < 15;++i){
        auto start = high_resolution_clock::now();
        int a = josephus_1(i,1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "For N="<<i<<" duration is: "<<duration.count() << " milliseconds with result= "<<a<<endl;
    }
    return 0;
}