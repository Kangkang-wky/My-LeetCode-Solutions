#include "../include/help.h"

/**
 * @brief 单例模式是C++的一种设计模式，其核心思想是确保一个类中只有一个实例，
 *        也就是说一个类中仅有一个对象，且能被其他变量访问。相当于创建了一个全局变量。
 * 
 * 使用场景:         
 *      （1）资源共享：例如log/配置文件等在整个程序中都需要使用，使用单例模式可以确保这些资源都仅有一个实例，避免资源浪费。
        （2）数据：用来缓存数据的数据结构，需要在一处写，多处读取/多处写，多处读取。
        （3）单元测试：可以用来创建单元类，搭建单元测试框架。
 *
 *      （1）私有化构造函数：防止外界创建单例类的对象，不需要赋值。
        （2）静态成员变量：提供一个自身的静态私有成员变量，以指向类的实例。
        （3）静态方法：提供一个公有的静态成员函数，用来返回这个唯一实例。
 */




class Singleton {
public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex);  // 加锁确保线程安全
            if (instance == nullptr) {
                instance = new Singleton();
            }
        }
        return instance;
    }

private:
    Singleton() {}  // 构造函数私有化
    ~Singleton() {}

    Singleton(const Singleton&) = delete;  // 禁止拷贝构造函数
    Singleton& operator=(const Singleton&) = delete;  // 禁止赋值

    static Singleton* instance;
    static std::mutex mutex;  // 互斥锁
};

// 静态实例初始化为空指针
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;

