#include "../include/help.h"

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

