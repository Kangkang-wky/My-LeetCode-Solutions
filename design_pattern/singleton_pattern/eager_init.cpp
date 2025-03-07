#include "../include/help.h"

class Singleton {
public:
    // 提供静态的访问方式
    static Singleton& getInstance() {
        return instance;  // 直接返回静态实例
    }

    void showMessage() {
        cout << "Singleton instance is working!" << endl;
    }

private:
    Singleton() { cout << "Singleton Constructor Called!" << endl; }  // 构造函数私有化
    ~Singleton() { cout << "Singleton Destructor Called!" << endl; }

    Singleton(const Singleton&) = delete;  // 禁止拷贝构造函数
    Singleton& operator=(const Singleton&) = delete;  // 禁止赋值

    static Singleton instance;  // 静态实例，程序启动时创建
};

// 静态实例必须定义在类外
Singleton Singleton::instance;

int main() {
    // 通过调用 getInstance 来获取单例实例
    Singleton& s1 = Singleton::getInstance();
    s1.showMessage();

    // 由于我们不能复制实例，以下代码会编译错误：
    // Singleton s2 = Singleton::getInstance();  // 编译错误，不能复制单例

    // 单例是全局唯一的，只能通过 getInstance() 获取
    return 0;
}

