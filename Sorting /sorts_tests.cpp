#include "sorts.h"

int main() {
    
    std::vector<int> container1{28,   46,   45,   86,   55,    7,   10,   29,   50,   79,   70,   44,   97,   60,   40,   90,   8,9,   38,   36,   87,   75,   11,   52,   43,   39,   98,   93,    6 ,  82,   83 ,  35,   84 ,  33,   49,   32,   66,   15 ,  67,   24,   62,   13 ,  65 ,  74,   12,    2  , 20 ,  64,   96 ,  71,   61 ,  95 ,  47,   92 ,   8 ,  26,   48};
    std::vector<int> container2 = container1;
    std::vector<int> container3 = container1;
    std::vector<int> container4 = container1;

    std::cout<<std::endl<<std::endl;
    insertion_sort(container1);
    std::cout<<std::endl<<std::endl;
    heap_sort(container2);
    std::cout<<std::endl<<std::endl;
    shell_sort(container3);
    std::cout<<std::endl<<std::endl;
    bucket_sort(container4);
    std::cout<<std::endl<<std::endl;

    for (int i = 1; i < container1.size(); ++i){
        if (container1[i-1] > container1[i]){
            std::cout<<"[ERROR]: check index "<<i<<std::endl;
        }
    }

    if (container1 != container2){
        std::cout<<"[ERROR]: discrepancy between heap and insertion"<<std::endl;
    }
    if (container2 != container3){
        std::cout<<"[ERROR]: discrepancy between heap and shell"<<std::endl;
    }
    if (container3 != container4){
        std::cout<<"[ERROR]: discrepancy between shell and bucket"<<std::endl;
    }
    
    std::vector<int> empty;
    
    std::cout<<"Should print nothing..."<<std::endl;
    insertion_sort(empty);
    heap_sort(empty);
    shell_sort(empty);
    bucket_sort(empty);
    std::cout<<"continue..."<<std::endl;

    std::vector<int> ordered1;
    std::vector<int> ordered2;
    std::vector<int> ordered3;
    std::vector<int> ordered4;
    for (int i = 0; i < 40 ; ++i){
        ordered1.push_back(i);
    }
    ordered2 = ordered1;
    ordered3 = ordered1;
    ordered4 = ordered1;


    std::cout<<std::endl<<std::endl;
    insertion_sort(ordered1);
    std::cout<<std::endl<<std::endl;
    heap_sort(ordered2);
    std::cout<<std::endl<<std::endl;
    shell_sort(ordered3);
    std::cout<<std::endl<<std::endl;
    bucket_sort(ordered4);
    std::cout<<std::endl<<std::endl;

    for (int i = 1; i < ordered1.size(); ++i){
        if (ordered1[i-1] > ordered1[i]){
            std::cout<<"[ERROR]: check index "<<i<<std::endl;
        }
    }

    if (ordered1 != ordered2){
        std::cout<<"[ERROR]: discrepancy between heap and insertion"<<std::endl;
    }
    if (ordered2 != ordered3){
        std::cout<<"[ERROR]: discrepancy between heap and shell"<<std::endl;
    }
    if (ordered3 != ordered4){
        std::cout<<"[ERROR]: discrepancy between shell and bucket"<<std::endl;
    }





    return 0;
}
