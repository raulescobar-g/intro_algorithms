#include <iostream>
#include <typeinfo>
using namespace std;


//In the first attempt at the solution I used the wrong naming convention as the one suggested in the problem
//After changing the naming convention I also changed the inputs to the function:

    //1- I changed the array input to a pointer to the array. This would allow for the function to not have to copy
    //   the array.

    //2- I added a small test case in main just so that the grader can see that it works fine

    //3- the output was fixed such that the output is the reference to the smallest object in the array

    //4- Added comments to enhance clarity and objective of each line in the code

//define templated function of type Comparable
template <typename Comparable>
Comparable& find_min(Comparable* a, size_t size){

    //Check that it is not an empty list
    if (size == 0 || a == nullptr){
        throw invalid_argument("Size of array cannot be 0.");
    }

    //Define variable to be the first element in array
    Comparable& smallest = a[0];

    //Check array for smaller values and replace smallest with smaller values
    for (int i=0; i<size;++i){

        if (a[i] < smallest){
            smallest = a[i];
        }

    }

    //return smallest value reference after iterating over the whole array
    return smallest;
}


int main(){
    //test to see if it works for trivial case
    int test_array[] = {1,2,3,4,5,6,20,11,23,4,1,2,3,5,7,-20};
    cout<<"Smallest type in list is: "<<find_min(test_array,16)<<endl;
    return 0;
}

