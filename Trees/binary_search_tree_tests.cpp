
#include <iostream>
#include "binary_search_tree.h"
#include <sstream>
using std::cout;
using std::endl;

int main() {
    cout<<"Constructing empty tree..."<<endl;
    BinarySearchTree<int> tree;
    int array[17] = {50,25,75,12,37,62,87,6,18,32,42,56,68,81,93,100,1};

    cout<<"Trying self assignment..."<<endl;
    tree = tree;

    cout<<"Attempting exception catches, should catch empty tree: "<<endl;
    try{
        cout<<tree.find_max()<<endl;;
    }
    catch (std::invalid_argument(e)){
        cout<<"Error: "<<e.what()<<endl;
    }
    try{
        cout<<tree.find_min()<<endl;
    }
    catch (std::invalid_argument(e)){
        cout<<"Error: "<<e.what()<<endl;
    }

    cout<<"Inserting 17 items...";
    for (int i = 0; i < 17; ++i){
        tree.insert(array[i]);
    }
    cout<<"Inserting a duplicates..."<<endl;
    cout<<"Inserting 17 items...";
    for (int i = 0; i < 17; ++i){
        tree.insert(array[i]);
    }
    if (tree.contains(50)){
        cout<<"GOOD"<<endl;
    }
    if (tree.contains(12)){
        cout<<"GOOD"<<endl;
    }
    if (tree.contains(100)){
        cout<<"GOOD"<<endl;
    }
    if (!tree.contains(43)){
        cout<<"GOOD"<<endl;
    }

    cout<<"Done inserting"<<endl;
    cout<<"Printing tree..."<<endl;
    tree.print_tree();
    cout<<endl;
    cout<<"printing stats: "<<endl;
    cout<<"Min: "<<tree.find_min()<<endl;
    cout<<"Max: "<<tree.find_max()<<endl;

    cout<<"making a copy..."<<endl;
    BinarySearchTree<int> copy(tree);
    cout<<"Printing copied tree..."<<endl;
    copy.print_tree();
    cout<<endl;
    cout<<"printing copied stats: "<<endl;
    cout<<"copy Min: "<<copy.find_min()<<endl;
    cout<<"copy Max: "<<copy.find_max()<<endl;

    cout<<"Removing from main..."<<endl;
    tree.remove(1);
    tree.remove(50);
    tree.remove(100);
    tree.remove(56);
    tree.remove(6);
    tree.remove(1);
    tree.remove(62);
    tree.remove(25);
    tree.remove(100);
    tree.remove(42);
    tree.remove(68);
    tree.remove(12);
    cout<<"Printing tree..."<<endl;
    tree.print_tree();
    cout<<endl;
    cout<<"printing stats: "<<endl;
    cout<<"Min: "<<tree.find_min()<<endl;
    cout<<"Max: "<<tree.find_max()<<endl;

    cout<<"Printing copied tree..."<<endl;
    copy.print_tree();
    cout<<endl;
    cout<<"printing copied stats: "<<endl;
    cout<<"copy Min: "<<copy.find_min()<<endl;
    cout<<"copy Max: "<<copy.find_max()<<endl;

    cout<<"Using '=' operator for copy..."<<endl;
    copy = tree;
    cout<<"Printing copied tree..."<<endl;
    copy.print_tree();
    cout<<endl;
    cout<<"printing copied stats: "<<endl;
    cout<<"copy Min: "<<copy.find_min()<<endl;
    cout<<"copy Max: "<<copy.find_max()<<endl;


    int A[] = {63, 41, 76, 93, 66, 5, 10, 57, 8, 79, 29, 14, 73, 56, 54, 87, 60, 22, 23, 90};
    BinarySearchTree<int> tree1;
    for (size_t index = 0; index < 20; index++) {
    tree1.insert(A[index]);
    }
    tree1.print_tree();

    return 0;

    
}
