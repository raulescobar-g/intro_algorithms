#include "array_list.h"
#include "doubly_linked_list.h"
#include "stack.h"
#include "queue.h"

int main() {
    {
        ArrayList<int> list;
        list.size();
        list.insert(0, 0);
        list.operator[](0);
        list.remove(0);
    }
    
    {
        DoublyLinkedList<int> list;
        list.size();
        list.insert(0, 0);
        list.operator[](0);
        list.remove(0);
    }
    
    {
        Stack<int> stack;
        stack.push(0);
        stack.top();
        stack.pop();
    }
    
    {
        Queue<int> queue;
        queue.enqueue(0);
        queue.front();
        queue.dequeue();
    }
}
