#include "../include/help.h"

/**
 * @brief 队列实现, 实现链式队列部分
 * 
 * @tparam T 
 */


template <typename T>
class LinkQueue
{
public:
    LinkQueue()                     
    {
        peek = nullptr;
        rear = nullptr;
        count = 0;
    }
 
    ~LinkQueue()                      
    {
        while (!empty()) {
            dequeue();                  //将结点逐个释放
        }
    }
 
 
    void enqueue(T x)                   //入队
    {
        Node* s = new Node;             // 为新节点申请空间
        // 如果队列为空，peek和rear都指向新结点
        if (rear == nullptr) {
            s->data = x;
            s->next = nullptr;
            peek = rear = s;
        }
        else {  //如果队列非空，新结点插入队尾
            s->data = x;
            s->next = nullptr;
            rear->next = s;
            rear = s;
            
        }
        count++;
    }
 
 
    T dequeue()                         //出队
    {
        if (count == 0){
            throw "队列下溢";
        }
        Node* p = peek;
        T temp = peek->data;
        peek = peek->next;
        if (peek == nullptr){           // 如果队列变为空，则将rear也设置为nullptr
            rear = nullptr;
        }
        delete p;
        // 释放原队头节点的内存
        count--;
        return temp;
    }
 
 
    T front() const                  //取队头
    {
        if (count == 0) {
            throw "队列下溢";
        }
        return peek->data;
    }
 
 
    bool empty() const     
    {
        return count == 0;
    }
 
    int size() const         
    {
        return count;
    }
 
private:
    struct Node
    {
        T data;        // 数据域
        Node* next;    // 指针域
    };
    Node* peek;      
    Node* rear;     
    int count;        
 
};