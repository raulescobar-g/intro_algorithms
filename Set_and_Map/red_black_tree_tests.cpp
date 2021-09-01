#include "red_black_tree.h"

int main() {  
        
    RedBlackTree<int> tree;
    tree=tree;
    for (int i = 0; i < 1000000; ++i){
        tree.insert(i);
    }
    tree.print_tree();
    if (tree.contains(999999)){
        std::cout<<"success"<<std::endl;
    }


    return 0;
}