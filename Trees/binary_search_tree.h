#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdexcept>
#include <iostream>
#include <sstream>

template <typename Comparable>
class BinarySearchTree {
    public:
        BinarySearchTree();
        BinarySearchTree(const BinarySearchTree&);
        ~BinarySearchTree();
        BinarySearchTree& operator=(const BinarySearchTree&);
        bool contains(const Comparable&) const;
        void insert(const Comparable&);
        void remove(const Comparable&); //(use minimum of right child tree when value has two children)
        const Comparable& find_min() const; //throw std::invalid_argument if the tree is empty
        const Comparable& find_max() const; //throw std::invalid_argument if the tree is empty
        void print_tree(std::ostream& = std::cout) const;//print the tree (rotated 90 degrees to left, two spaces per level;“<empty>\n” if empty.
    
    private:
        struct TreeNode{
            Comparable data;
            TreeNode *left;
            TreeNode *right;
            TreeNode(const Comparable & theElement, TreeNode *lt, TreeNode *rt): data(theElement), left(lt), right(rt) { };
            TreeNode(const Comparable & theElement): data(theElement), left(nullptr), right(nullptr) { };
        };
        TreeNode *root;
        void copy_helper(TreeNode * & t,const TreeNode * copy_root);
        void make_empty(TreeNode * & t);
        TreeNode * find_min_helper(TreeNode *t) const;
        TreeNode * find_max_helper(TreeNode *t) const;
        void remove_helper(const Comparable& data, TreeNode * & t);
        void print_tree_helper(TreeNode *t,int space,std::stringstream& ss, std::ostream& = std::cout) const;
};

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(): root(nullptr){}

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree& copy){
    if (this != &copy){
        copy_helper(this->root,copy.root);
    }
}

template <typename Comparable>
void BinarySearchTree<Comparable>::copy_helper(TreeNode * & t,const TreeNode * copy_root){
    if (copy_root == nullptr){
        t = nullptr;
    }
    else{
        t = new TreeNode(copy_root->data);
        copy_helper(t->left,copy_root->left);
        copy_helper(t->right, copy_root->right);
    }
}

template <typename Comparable>
void BinarySearchTree<Comparable>::make_empty(TreeNode * & t){
    if (t != nullptr){
        make_empty(t->left);
        make_empty(t->right);
        delete t;
    }
    t = nullptr;
}

template <typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree(){
    make_empty(this->root);
}

template <typename Comparable>
BinarySearchTree<Comparable>& BinarySearchTree<Comparable>::operator=(const BinarySearchTree& copy){
    if (this != &copy){
        make_empty(this->root);
        copy_helper(this->root,copy.root);
    }
    return *this;
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable& data) const{
    TreeNode * t = root;
    while (t != nullptr){
        if (t->data < data){
            t = t->right;
        }
        else if (t->data > data){
            t = t->left;
        }
        else if (t->data == data){
            return true;
        }
    }
    return false;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& data){
    TreeNode * t = this->root;
    TreeNode * lag = nullptr;
    TreeNode * newNode = new TreeNode(data);

    if (this->root == nullptr){
        this->root = newNode;
        return;
    }
    while (t != nullptr){
        lag = t;
        if (data < t->data){
            t = t->left;;
        }
        else if (data > t->data){
            t = t->right;
        }
        else{
            return;
        }
    }
    if (lag->data > data){
        lag->left = newNode;
    }
    else{
        lag->right = newNode;
    }
    
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove_helper(const Comparable& data, TreeNode * & t){
    if( t == nullptr )
        return; // Item not found; do nothing
    if(data < t->data){
        remove_helper(data, t->left);
    }
    else if(t->data < data){
        remove_helper(data, t->right);
    }
    else if(t->left != nullptr && t->right != nullptr){
        t->data = find_min_helper(t->right)->data;
        remove_helper(t->data, t->right);
    }
    else{
        TreeNode *oldNode = t;
        t = ( t->left != nullptr ) ? t->left : t->right;
        delete oldNode;
    }
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable& data){
    remove_helper(data,this->root);
}

template <typename Comparable>
const Comparable& BinarySearchTree<Comparable>::find_min() const{
    TreeNode * t = this->root;
    if (t == nullptr){
        throw std::invalid_argument("Empty tree");
    }
    while (t->left != nullptr){
        t = t->left;
    }
    return t->data;
} //throw std::invalid_argument if the tree is empty

template <typename Comparable>
typename BinarySearchTree<Comparable>::TreeNode * BinarySearchTree<Comparable>::find_min_helper(TreeNode *t) const{
    if (t == nullptr){
        throw std::invalid_argument("Empty tree");
    }
    while (t->left != nullptr){
        t = t->left;
    }
    return t;
} //throw std::invalid_argument if the tree is empty

template <typename Comparable>
const Comparable& BinarySearchTree<Comparable>::find_max() const{
    TreeNode * t = this->root;
    if (t == nullptr){
        throw std::invalid_argument("Empty tree");
    }
    while (t->right != nullptr){
        t = t->right;
    }
    return t->data;
} //throw std::invalid_argument if the tree is empty

template <typename Comparable>
typename BinarySearchTree<Comparable>::TreeNode * BinarySearchTree<Comparable>::find_max_helper(TreeNode *t) const{
    if (t == nullptr){
        throw std::invalid_argument("Empty tree");
    }
    while (t->right != nullptr){
        t = t->right;
    }
    return t;
} //throw std::invalid_argument if the tree is empty

template <typename Comparable>
void BinarySearchTree<Comparable>::print_tree(std::ostream& out) const{
    //out.rdbuf(std::cout.rdbuf());
    std::stringstream ss;
    TreeNode * t = root;
    if (t == nullptr){
        out<<"<empty>\n";
        return;
    }
    print_tree_helper(t,0,ss);
    out<<ss.str();
}

template <typename Comparable>
void BinarySearchTree<Comparable>::print_tree_helper(TreeNode *t, int space,std::stringstream& ss,std::ostream& out) const{
    //out.rdbuf(std::cout.rdbuf());
    if (t == nullptr) {
        return;
    }
    space += 2;
    print_tree_helper(t->right,space,ss);
    //out<<std::endl;
    for (int i = 2; i< space;++i){
        ss<<" ";
    }
    ss<<t->data<<"\n";
    print_tree_helper(t->left,space,ss);
}


#endif