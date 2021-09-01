#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

//Node struct needed for linked list
template <typename T>
struct Node {
    Node(T data): data(data), next(nullptr){} 
    T data;
    Node* next;
};

// templated single linked list
// has print,average,push, and pop
template <class T>
class list{
    public:
        list(): head(nullptr),tail(nullptr){
            this->sz = 0;
        }
        list(T data){
            this->sz = 1;
            Node<T> *newNode = new Node<T>(data);
            this->head = newNode;
            this->tail = newNode;
        }
        ~list(){
            Node<T>* temp;
            while (head != nullptr){
                temp = head;
                head = head->next;
                delete temp;
            }
            tail = nullptr;
            this->sz = 0;
        }
        list(const list<T>& original){
            Node<T> *iterator;
            iterator = original.head;
            if (iterator == nullptr){
            this->head = nullptr;
            this->tail = nullptr;
            this->sz = 0;
            }
            else{
                Node<T> *newNode = new Node<T>(original.head->data);
                this->tail = this->head = newNode;
                iterator = iterator->next;
                while (iterator != nullptr){
                    this->push_back(iterator->data);
                    iterator = iterator->next;
                }
                this->sz = original.sz;
            }
        }
        list<T>& operator=(const list<T>& original){
            Node<T> *iterator;
            iterator = original.head;
            if (iterator == nullptr){
            this->head = nullptr;
            this->tail = nullptr;
            this->sz = 0;
            }
            else{
                Node<T> *newNode = new Node<T>(original.head->data);
                this->tail = this->head = newNode;
                iterator = iterator->next;
                while (iterator != nullptr){
                    this->push_back(iterator->data);
                    iterator = iterator->next;
                }
                this->sz = original.sz;
            }
            return *this;
        }
        void push(T data){
            if (head == nullptr){
                Node<T> *newNode = new Node<T>(data);
                head = newNode;
                tail = newNode;
                sz += 1;
            }
            else {
                sz += 1;
                Node<T> *newNode = new Node<T>(data);
                tail->next = newNode;
                tail = newNode;
                if (head->next == nullptr){
                    head->next = newNode;
                }
            }
        }
        void print(){
            Node<T> *iterator;
            iterator = head;
            int elements = 0;
            while (iterator != nullptr){
                elements += 1;
                cout <<"Element "<<elements<<": " <<iterator->data<<endl;
                iterator = iterator->next;
            }
        }
        void avg(){
            Node<T> *iterator = head;
            double sum = 0;
            while (iterator != nullptr){
                sum += iterator->data;
                iterator = iterator->next;
            }
            sum = sum / (double)sz;
            cout << "Average: "<< sum <<endl;
        }
        void pop(int i){
            if (sz == 0){
                cout <<"no elements"<<endl;
            }
            else if (sz == 1){
                head = nullptr;
                tail = nullptr;
                sz = 0;
            }
            else if (i == 0){
                Node<T> *iterator = head;
                head = head->next;
                delete iterator;
                iterator = nullptr;
                sz -= 1;
            }
            else{
                Node<T> *iterator = head;
                Node<T> *lag = nullptr;
                int index = 0;
                while (index != i){
                    lag = iterator;
                    iterator = iterator->next;
                    index += 1;
                }
                lag->next = iterator->next;
                delete iterator;
                iterator = nullptr;
                sz -= 1;
            }
        }
    private:
        Node<T> *head;
        Node<T> *tail;
        unsigned int sz;
};


int main(){
    list <int>list1(10);
    list1.push(21);
    list1.push(15);
    list1.push(21);
    list1.push(2);
    list1.push(21);
    //list1.pop(2);
    //list1.avg();
    list1.print();
    return 0;
}






















