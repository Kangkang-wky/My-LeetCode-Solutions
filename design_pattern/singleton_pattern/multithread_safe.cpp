
/**
 * @brief 优点：
            简洁、线程安全。
            在程序启动时不会立即创建实例，而是等到第一次使用时创建。
            不需要显式加锁。
          缺点：
            只适用于需要在第一次使用时实例化的情况。
 * 
 */


class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;  // 静态局部变量
        return instance;
    }

private:
    Singleton() {}  // 构造函数私有化
    ~Singleton() {}

    Singleton(const Singleton&) = delete;  // 禁止拷贝构造函数
    Singleton& operator=(const Singleton&) = delete;  // 禁止赋值
};
