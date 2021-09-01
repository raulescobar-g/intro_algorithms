#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <stdexcept>
#include <iostream>
#include <sstream>


template <typename Comparable>
class RedBlackTree {

    public:
        enum Color {RED, BLACK};
    
        struct Node {
            Comparable data;
            int color;
            Node * right;
            Node * left;
            Node * parent;
            Node(const Comparable & data): data(data),color(RED), left(nullptr), right(nullptr), parent(nullptr) {};
        };

        RedBlackTree(); //done
        RedBlackTree(const RedBlackTree&); //done
        ~RedBlackTree(); //done
        RedBlackTree& operator=(const RedBlackTree&); //done

        void insert(const Comparable&);//done
        void remove(const Comparable&); //done

        bool contains(const Comparable&) const; //done
        const Comparable& find_min() const; //done
        const Comparable& find_max() const; //done

        int color(const Node*  node) const; //done
        const Node* get_root() const; //done

        void print_tree(std::ostream& = std::cout) const; //done
    
    private:
        Node * root;
        void copy_helper(Node * & t,const Node * copy_root); //done
        void make_empty(Node * & t); //done
        void double_clockwise(Node *& t); //done
        void double_counter_clockwise(Node *& t); //done
        void clockwise(Node *& t); //done
        void counter_clockwise(Node *& t); //done
        void print_tree_helper(Node *t,int space, std::stringstream& ss,std::ostream& = std::cout) const; //done
        void remove_helper(Node *& t, const Comparable& target);//done
};

template <typename Comparable>
RedBlackTree<Comparable>::RedBlackTree(): root(nullptr){}

template <typename Comparable>
RedBlackTree<Comparable>::RedBlackTree(const RedBlackTree& copy){
    if (this != &copy){
        copy_helper(this->root,copy.root);
    }
}

template <typename Comparable>
void RedBlackTree<Comparable>::copy_helper(Node * & t,const Node * copy_root){
    if (copy_root == nullptr){
        t = nullptr;
    }
    else{
        t = new Node(copy_root->data);
        t->color = copy_root->color;
        copy_helper(t->left,copy_root->left);
        copy_helper(t->right, copy_root->right);

        if (t->right != nullptr){
            t->right->parent = t;
        }
        if (t->left != nullptr){
            t->left->parent = t;
        }
    }
}

template <typename Comparable>
RedBlackTree<Comparable>::~RedBlackTree(){
    make_empty(this->root);
}

template <typename Comparable>
void RedBlackTree<Comparable>::make_empty(Node * & t){
    if (t != nullptr){
        make_empty(t->left);
        make_empty(t->right);
        delete t;
    }
    t = nullptr;
}

template <typename Comparable>
RedBlackTree<Comparable>& RedBlackTree<Comparable>::operator=(const RedBlackTree& copy){
    if (this != &copy){
        make_empty(this->root);
        copy_helper(this->root,copy.root);
    }
    return *this;
}

template <typename Comparable>
bool RedBlackTree<Comparable>::contains(const Comparable& target) const{
    if (this->root == nullptr){
        return false;
    }
    else{
        Node * iter = this->root;
        while (iter != nullptr){
            if (iter->data < target){
                iter = iter->right;
            }
            else if (iter->data > target){
                iter = iter->left;
            }
            else if (iter->data == target){
                return true;
            }
        }
        return false;
    }
}

template <typename Comparable>
const Comparable& RedBlackTree<Comparable>::find_min() const{
    if (this->root == nullptr){
        throw std::invalid_argument("Tree empty");
    }
    else{
        Node * iter = this->root;
        while (iter->left != nullptr){
            iter = iter->left;
        }
    return iter->data;
    }
}

template <typename Comparable>
const Comparable& RedBlackTree<Comparable>::find_max() const{
    if (this->root == nullptr){
        throw std::invalid_argument("Tree empty");
    }
    else{
        Node * iter = this->root;
        while (iter->right != nullptr){
            iter = iter->right;
        }
    return iter->data;
    }
}

template <typename Comparable>
int RedBlackTree<Comparable>::color(const Node* node) const{
    if (node == nullptr ){
        return BLACK;
    }
    else {
        return node->color;
    }
}

template <typename Comparable>
const typename RedBlackTree<Comparable>::Node* RedBlackTree<Comparable>::get_root() const {
    return this->root;
}

template <typename Comparable>
void RedBlackTree<Comparable>::insert(const Comparable& package){
    if (this->root == nullptr){
        this->root = new Node(package);
        this->root->color = BLACK;
    }
    else{
        Node * newNode = new Node(package);
        Node * lag;
        Node * iter = this->root;
        while (iter != nullptr){
            lag = iter;
            if (iter->data < package){
                iter = iter->right;
                
            }
            else if (iter->data > package){
                
                iter = iter->left;
            }
            else if (iter->data == package){
                return;
            }
        }
        //std::cout<<"inserting : "<<package<<std::endl;
        if (lag->data < package){
            lag->right = newNode;  
            iter = lag->right;
        }
        else{
            lag->left = newNode;
            iter = lag->left;
        }
        newNode->parent = lag;
        //std::cout<<"inserted done : "<<package<<std::endl;
        //std::cout<<std::endl;
        //print_tree();
        //std::cout<<std::endl;
        if (lag->color == BLACK){
            return;
        }
        else{
            
            //std::cout<<"fault"<<std::endl;
            while (iter != this->root && color(iter) == RED){
                //std::cout<<"fault"<<std::endl;
                Node * check = lag;
                lag = lag->parent;
                if (lag == nullptr){
                    return;
                }
                //std::cout<<"fault"<<std::endl;
                if (lag->left == check){
                    //std::cout<<"fault"<<std::endl;
                    if (color(lag->right) == RED){
                        lag->left->color = BLACK;
                        lag->color = RED;
                        lag->right->color = BLACK;
                        iter = lag;
                        lag = lag->parent;
                    }
                    else{
                        //std::cout<<"fault"<<std::endl;
                        if (lag->left->right == iter){
                            //std::cout<<"fault"<<std::endl;
                            counter_clockwise(lag->left);
                            iter = iter->left;
                        }
                        clockwise(lag);
                        iter->parent->color = BLACK;
                        iter->color = RED;
                        lag->color = RED;
                        lag = lag->parent->parent;
                        iter = iter->parent;
                    }
                }
                else{
                    //std::cout<<"fault"<<std::endl;
                    if (color(lag->left) == RED) {
                        //std::cout<<"fault"<<std::endl;
                        lag->left->color = BLACK;
                        lag->color = RED;
                        lag->right->color = BLACK;
                        iter = lag;
                        lag = lag->parent;
                    }
                    else{
                        //std::cout<<"fault"<<std::endl;
                        if (iter == lag->right->left){
                            //std::cout<<"fault"<<std::endl;
                            clockwise(lag->right);
                            iter = iter->right;
                        }
                        //std::cout<<"fault"<<std::endl;
                        counter_clockwise(lag);
                        //std::cout<<"fault"<<std::endl;
                        iter->parent->color = BLACK;
                        iter->color = RED;
                        lag->color = RED;
                        lag = lag->parent->parent;
                        iter = iter->parent;
                        //std::cout<<"fault"<<std::endl;
                    }
                }
            }
            this->root->color = BLACK;
        }
    }
}

template <typename Comparable>
void RedBlackTree<Comparable>::remove(const Comparable& target){
    remove_helper(this->root,target);
}

template <typename Comparable>
void RedBlackTree<Comparable>::remove_helper(Node *& iter, const Comparable& target){
    if (iter == nullptr){
        return;
    }
    else{
        while (iter != nullptr){
            if (iter->data < target){
                remove_helper(iter->right, target);
            }
            else if (iter->data > target){
                remove_helper(iter->left, target);
            }
            else if (iter->data == target){








                //WE FOUND THE NODE TO DELETE///////////////////////////////////////////////////////////////////////////////
                Node * lag = iter->parent;
                if (iter->left == nullptr && iter->right == nullptr){//NO CHILDREN
                    Node * x = iter->right;
                    if (color(iter) == RED){
                        delete iter;
                        return;
                    }
                    else{





                    }
                }











                else if (iter->left != nullptr && iter->right != nullptr){//TWO CHILDREN
                    Node * min = iter->right;
                    while (min->left != nullptr){
                        min =  min->left;
                    }
                    Node * x = min->right;
                    if (color(iter) == RED){
                        if (color(min) == RED){
                            iter->data = min->data;
                        }
                    }
                    else{

                    }

                }













                else{//ONE CHILD
                    if (iter->left != nullptr){
                        Node * x = iter->left;
                    } 
                    else{
                        Node * x = iter->right;
                    }
                    if (color(iter) == RED){
                        if(color(x) == RED){
                            TreeNode *oldNode = iter;
                            iter = ( iter->left != nullptr ) ? iter->left : iter->right;
                            delete oldNode;
                            return;
                        }
                        else{
                            TreeNode *oldNode = iter;
                            iter = ( iter->left != nullptr ) ? iter->left : iter->right;
                            delete oldNode;
                        }
                    }

                }
            }

        }
    }

}



template <typename Comparable>
void RedBlackTree<Comparable>::clockwise(Node *& t){
    //std::cout<<"fault clocky"<<std::endl;
    Node * spin = t->left;
    spin->parent = t->parent;
    //std::cout<<"fault clocky"<<std::endl;
    t->parent = spin;
    t->left = spin->right;
    //std::cout<<"fault clocky"<<std::endl;
    if (t->left != nullptr){
        t->left->parent = t;
    }
    spin->right = t;
    if (this->root->data == t->data){
        this->root = spin;
    }
    else{
        spin->parent->left = spin;
    }
}

template <typename Comparable>
void RedBlackTree<Comparable>::counter_clockwise(Node *& t){
    //std::cout<<"fault clocky"<<std::endl;
    Node * spin = t->right;
    spin->parent = t->parent;
    //std::cout<<"fault clocky"<<std::endl;
    t->parent = spin;
    t->right = spin->left;
    spin->left = t;
    //std::cout<<"fault clocky"<<std::endl;
    if (t->right != nullptr){
        t->right->parent = t;
    }
    //std::cout<<"fault clocky"<<std::endl;
    if (this->root->data == t->data){
        this->root = spin;
    }
    else{
        spin->parent->right = spin;
    }
}


template <typename Comparable>
void RedBlackTree<Comparable>::double_clockwise(Node *& t){
    counter_clockwise(t->left);
    clockwise(t);
}

template <typename Comparable>
void RedBlackTree<Comparable>::double_counter_clockwise(Node *& t){
    clockwise(t->right);
    counter_clockwise(t);
}

template <typename Comparable>
void RedBlackTree<Comparable>::print_tree(std::ostream& out) const{
    
    std::stringstream ss;
    Node * t = root;
    if (t == nullptr){
        out<<"<empty>\n";
        return;
    }
    print_tree_helper(t,0,ss);
    out<<ss.str();
}

template <typename Comparable>
void RedBlackTree<Comparable>::print_tree_helper(Node *t, int space,std::stringstream& ss,std::ostream& out) const{

    if (t == nullptr) {
        return;
    }
    space += 4;
    print_tree_helper(t->right,space,ss);
    out<<std::endl;
    for (int i = 2; i< space;++i){
        ss<<" ";
    }
    ss<<t->data<<","<<t->color<<"\n";
    print_tree_helper(t->left,space,ss);
}

#endif  // RED_BLACK_TREE_H