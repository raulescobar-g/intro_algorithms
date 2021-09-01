#include <iostream>
#include "avl_tree.h"

using std::cout;
using std::endl;

int main() {
    cout<<"Constructing empty tree..."<<endl;
    AVLTree<int> tree;

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
    int b = 0;
    int c = 0;
    cout<<"Inserting 50 items..."<<endl;
    for (int i = 0; i < 50; ++i){
        tree.insert(i);
        b = tree.find_min();
        c = tree.find_max();
        //tree.print_tree();
    }
    //tree.print_tree();
    cout<<"Inserting 50 items..."<<endl;
    for (int i = 100; i > 51; --i){
        tree.insert(i);
        b = tree.find_min();
        c = tree.find_max();
        
    }
    bool a;
    for (int i = 0 ; i < 100 ; ++i){
        a = tree.contains(i);
    }
    cout<<"Inserting a duplicates..."<<endl;
    cout<<"Inserting 10 items...";
    for (int i = 0; i < 10; ++i){
        tree.insert(i);
    }
    cout<<endl;
    if (tree.contains(50)){
        cout<<"GOOD"<<endl;
    }
    if (tree.contains(12)){
        cout<<"GOOD"<<endl;
    }
    if (tree.contains(100)){
        cout<<"GOOD"<<endl;
    }
    if (!tree.contains(1000)){
        cout<<"GOOD"<<endl;
    }
    if (tree.contains(-1)){
        cout<<"GOOD"<<endl;
    }
    if (tree.contains(76)){
        cout<<"GOOD"<<endl;
    }
    if (tree.contains(0)){
        cout<<"GOOD"<<endl;
    }
    if (!tree.contains(101)){
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
    AVLTree<int> copy(tree);
    cout<<"Printing copied tree..."<<endl;
    copy.print_tree();
    cout<<endl;
    cout<<"printing copied stats: "<<endl;
    cout<<"copy Min: "<<copy.find_min()<<endl;
    cout<<"copy Max: "<<copy.find_max()<<endl;

    cout<<"Removing from main..."<<endl;
    for (int i = -10; i < 40; ++i){
        tree.remove(i);
        b = tree.find_min();
        c = tree.find_max();
    }
    for (int i = 30; i < 62; ++i){
        tree.remove(i);
        b = tree.find_min();
        c = tree.find_max();
    }
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
    copy = copy;
    tree = copy;
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
    for (int i = 0; i < 110; ++i){
        tree.remove(i);
        copy.remove(i);
    }
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
    try{
        cout<<copy.find_max()<<endl;;
    }
    catch (std::invalid_argument(e)){
        cout<<"Error: "<<e.what()<<endl;
    }
    try{
        cout<<copy.find_min()<<endl;
    }
    catch (std::invalid_argument(e)){
        cout<<"Error: "<<e.what()<<endl;
    }
    tree.print_tree();
    copy.print_tree();
    int A[] = {63, 41, 76, 93, 66, 5, 10, 57, 8, 79, 29, 14, 73, 56, 54, 87, 60, 22, 23, 90};
    AVLTree<int> tree1;
    for (size_t index = 0; index < 20; index++) {
    tree1.insert(A[index]);
    }
    tree1.print_tree();
    return 0;
}