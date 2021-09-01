#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <stdexcept>
#include <iostream>
#include <sstream>
using std::max;

template <typename Comparable>
class AVLTree {
    public:
        AVLTree();
        AVLTree(const AVLTree&);
        ~AVLTree();
        AVLTree& operator=(const AVLTree&);
        bool contains(const Comparable&) const;
        void insert(const Comparable&);
        void remove(const Comparable&); //(use minimum of right child tree when value has two children)
        const Comparable& find_min() const; //throw std::invalid_argument if the tree is empty
        const Comparable& find_max() const; //throw std::invalid_argument if the tree is empty
        void print_tree(std::ostream& = std::cout) const;//print the tree (rotated 90 degrees to left, two spaces per level;“<empty>\n” if empty.
    
    private:
        struct TreeNode{
            Comparable data;
            int height;
            TreeNode *left;
            TreeNode *right;
            TreeNode(const Comparable & data, int height): data(data),height(height), left(nullptr), right(nullptr) { };
        };
        TreeNode *root;
        int BALANCE_COEFFICIENT;
        void copy_helper(TreeNode * & t,const TreeNode * copy_root);
        void make_empty(TreeNode * & t);
        TreeNode * find_min_helper(TreeNode *t) const;
        TreeNode * find_max_helper(TreeNode *t) const;
        void remove_helper(const Comparable& data, TreeNode * & t);
        void print_tree_helper(TreeNode *t,int space, std::stringstream& ss,std::ostream& = std::cout) const;
        void balance(TreeNode *& t);
        void double_clockwise(TreeNode *& t);
        void double_counter_clockwise(TreeNode *& t);
        void clockwise(TreeNode *& t);
        void counter_clockwise(TreeNode *& t);
        int height(TreeNode *t) const;
        void insert_helper(const Comparable& data, TreeNode *& t);
        
};



template <typename Comparable>
int AVLTree<Comparable>::height(TreeNode *t) const{
    return t == nullptr ? -1 : t->height;
}

template <typename Comparable>
void AVLTree<Comparable>::balance(TreeNode *& t){
    //std::cout<<"balancing..."<<std::endl;
    if (t == nullptr){
        return;
    }
    //std::cout<<"Coeff check..."<<std::endl;
    if ((height(t->left) - height(t->right)) >= BALANCE_COEFFICIENT){
        //std::cout<<"right left heights: "<<height(t->right)<<" : "<<height(t->left) <<std::endl;
        //std::cout<<"Balance coef: "<<(height(t->left) - height(t->right))<<std::endl;
        //std::cout<<"oops1"<<std::endl;
        if (height(t->left->left) >= height(t->left->right)){
            clockwise(t);
        }
        else{
            double_clockwise(t);
        }
    }
    else if ((height(t->right) - height(t->left)) >= BALANCE_COEFFICIENT){
        //std::cout<<"oops2"<<std::endl;
        if (height(t->right->right) >= height(t->right->left)){
            counter_clockwise(t);
        }
        else{
            double_counter_clockwise(t);
        }
    }
    //std::cout<<"balanced..."<<std::endl;
    t->height = max(height(t->left),height(t->right))+1;
}

template <typename Comparable>
void AVLTree<Comparable>::clockwise(TreeNode *& t){
    TreeNode * spin = t->left;
    t->left = spin->right;
    spin->right = t;
    t->height = max(height(t->left),height(t->right)) + 1;
    spin->height = max(height(spin->left),t->height) + 1;
    t = spin;
}

template <typename Comparable>
void AVLTree<Comparable>::counter_clockwise(TreeNode *& t){
    TreeNode * spin = t->right;
    t->right = spin->left;
    spin->left = t;
    t->height = max(height(t->left),height(t->right)) + 1;
    spin->height = max(height(spin->right),t->height) + 1;
    t = spin;
}


template <typename Comparable>
void AVLTree<Comparable>::double_clockwise(TreeNode *& t){
    counter_clockwise(t->left);
    clockwise(t);
}

template <typename Comparable>
void AVLTree<Comparable>::double_counter_clockwise(TreeNode *& t){
    clockwise(t->right);
    counter_clockwise(t);
}


template <typename Comparable>
AVLTree<Comparable>::AVLTree(): root(nullptr),BALANCE_COEFFICIENT(2){}

template <typename Comparable>
AVLTree<Comparable>::AVLTree(const AVLTree& copy): BALANCE_COEFFICIENT(2){
    if (this != &copy){
        copy_helper(this->root,copy.root);
    }
}

template <typename Comparable>
void AVLTree<Comparable>::copy_helper(TreeNode * & t,const TreeNode * copy_root){
    if (copy_root == nullptr){
        t = nullptr;
    }
    else{
        t = new TreeNode(copy_root->data,copy_root->height);
        copy_helper(t->left,copy_root->left);
        copy_helper(t->right, copy_root->right);
    }
}

template <typename Comparable>
void AVLTree<Comparable>::make_empty(TreeNode * & t){
    if (t != nullptr){
        make_empty(t->left);
        make_empty(t->right);
        delete t;
    }
    t = nullptr;
}

template <typename Comparable>
AVLTree<Comparable>::~AVLTree(){
    make_empty(this->root);
}

template <typename Comparable>
AVLTree<Comparable>& AVLTree<Comparable>::operator=(const AVLTree& copy){
    if (this != &copy){
        make_empty(this->root);
        copy_helper(this->root,copy.root);
    }
    return *this;
}

template <typename Comparable>
bool AVLTree<Comparable>::contains(const Comparable& data) const{
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
void AVLTree<Comparable>::insert(const Comparable& data){
    //std::cout<<"Inserting : "<<data<<std::endl;
    insert_helper(data,this->root);
}

template <typename Comparable>
void AVLTree<Comparable>::insert_helper(const Comparable& data, TreeNode *& t){
    
    if (t == nullptr){
        t = new TreeNode(data,0);
    }
    else if (data < t->data){
        insert_helper(data,t->left);
    }
    else if (data > t->data){
        insert_helper(data,t->right);
    }
    //std::cout<<"Balancing :"<<t->data<<std::endl;
    balance(t);

}

template <typename Comparable>
void AVLTree<Comparable>::remove_helper(const Comparable& data, TreeNode * & t){
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
    balance(t);
}

template <typename Comparable>
void AVLTree<Comparable>::remove(const Comparable& data){
    remove_helper(data,this->root);
}

template <typename Comparable>
const Comparable& AVLTree<Comparable>::find_min() const{
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
typename AVLTree<Comparable>::TreeNode * AVLTree<Comparable>::find_min_helper(TreeNode *t) const{
    if (t == nullptr){
        throw std::invalid_argument("Empty tree");
    }
    while (t->left != nullptr){
        t = t->left;
    }
    return t;
} //throw std::invalid_argument if the tree is empty

template <typename Comparable>
const Comparable& AVLTree<Comparable>::find_max() const{
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
typename AVLTree<Comparable>::TreeNode * AVLTree<Comparable>::find_max_helper(TreeNode *t) const{
    if (t == nullptr){
        throw std::invalid_argument("Empty tree");
    }
    while (t->right != nullptr){
        t = t->right;
    }
    return t;
} //throw std::invalid_argument if the tree is empty

template <typename Comparable>
void AVLTree<Comparable>::print_tree(std::ostream& out) const{
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
void AVLTree<Comparable>::print_tree_helper(TreeNode *t, int space,std::stringstream& ss,std::ostream& out) const{
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