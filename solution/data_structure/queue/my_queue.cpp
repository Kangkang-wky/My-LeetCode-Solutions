#include "../include/help.h"

/**
 * @brief 思路 通过 instack 和 outstack 来回倒腾
 * 
 */

class MyQueue {
private:
    stack<int> inStack, outStack;

    void in2out() {
        while (!inStack.empty()) {
            outStack.push(inStack.top());
            inStack.pop();
        }
    }

public:
    MyQueue() {}

    void push(int x) {
        inStack.push(x);
    }

    int pop() {
        if (outStack.empty()) {
            in2out();
        }
        int x = outStack.top();
        outStack.pop();
        return x;
    }

    int peek() {
        if (outStack.empty()) {
            in2out();
        }
        return outStack.top();
    }

    bool empty() {
        return inStack.empty() && outStack.empty();
    }
};


/**
 * @brief 不借助 STL 实现队列, 大抵有两种方式, 一种方式是顺序队列的方式, 一种是链式队列的方式
 *        顺序队列的方式采用数组实现, 链式队列的方式采用
 * 
 */

class MyQueue_array {
private:
    //数组
    int *queue;
    int front;
    int rear;
    int size;
 
public:
    //构造函数
    MyQueue_array(int queueSize = 10): size(queueSize), front(0), rear(0) {
        this->queue=new int[queueSize];
    }
  
    //析构函数
    ~ MyQueue_array() {
        delete[] queue;
    }
    
    //队列是否为空
    bool isEmpty() {
        return this->front==this->rear;
    }

    //数据入队列
    bool push_back(int data) {
        //需要判断队列是否有空位置
        if (((this->rear+1) % this->size)!=this->front) {
            //获取当前可存储位置
            this->rear=(this->rear+1) % this->size;
            //存储数据
            this->queue[this->rear]=data;
            return true;
        }
        return false;
    }

    //数据出队列
    bool pop_front(int& data) {
        //队列不能为空
        if (this->rear!=this->front) {
            //头指针向右移动
            this->front=(this->front+1) % this->size;
            data=this->queue[this->front];
            return true;
        }
        return false;
    }

    //查看队头数据
    bool get_front(int& data) {
        //队列不能为空
        if (this->rear!=this->front) {
            //头指针向右移动
            int idx=(this->front+1) % this->size;
            data=this->queue[idx];
            return true;
        }
        return false;
    }
};


//链表的结点类型
struct QueueNode {
    int data;
    QueueNode* next;
    QueueNode() {
        this->next = NULL;
    };
};
class MyQueue_list {
private:
    //数组
    QueueNode* front;
    QueueNode* rear;

public:
  //构造函数
    MyQueue_list() {
        this->front = NULL;
        this->rear = NULL;
    }
    
    //析构函数
    ~MyQueue_list() {
        QueueNode* p, *q;
        p=front;
        while(p) {
            q=p;
            p=p->next;
            delete q;
        }
        front = NULL;
        rear = NULL;
    }

    //队列是否为空
    bool isEmpty() {
        return this->front==NULL && this->rear==NULL;
    }
    
    //数据入队列
    bool push_back(int data) {
        //新结点
        QueueNode* p = new QueueNode();
        // 申请节点成功
        if(p) {
            //申请结点成功
            p->data=data;
            if(rear) {      // 查询 rear 节点是否非空
                rear->next=p;
                rear=p;
            } 
            else {
                front=rear=p;
            }
            return true;
        } 
        else {
            return false;
        }
            
    }
    //数据出队列
    bool pop_front(int& data) {
        QueueNode* p;
        if(!isEmpty()) {   //判断队列是否为空
            p = front;
            data = p->data;
            front = front->next;
            if(!front) {
                rear=NULL;
            }
            delete p;
            return true;
        }
        return false;
    }
    //查看队头数据
    bool get_front(int & data) {
        if(!isEmpty()) {
            data=front->data;
            return true;
        } 
        else {
            return false;
        }    
    }
};