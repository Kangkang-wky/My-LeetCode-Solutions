
#include <atomic>
#include <iostream>
#include <memory>
#include <type_traits>
namespace smart_ptr {

// shared_ptr 指针类
template <typename T> struct shared_ptr;
// weak_ptr 指针类
template <typename T> struct weak_ptr;
// enable_shared_from_this 类 如果用一句话描述的话就是为访问对象的 this 指针
// 提供一个 shared_ptr 版本
template <class T> struct enable_shared_from_this;

// std::is_base_of_v 检查第一个指定的类型是否为第二个类型的基类
template <typename T>
constexpr auto can_enable_shared =
    std::is_base_of_v<enable_shared_from_this<T>, T>;

// 引用计数类实现: 强引用计数 与 弱引用计数
template <typename T> struct RefCount {
  RefCount(T *raw_ptr) : _ptr(raw_ptr) {}

  void add_ref() { _uses++; }

  void sub_ref() {
    if ((--_uses) == 0) {
      // 引用计数为 0, 销毁对象
      destroy_resource();
      // 弱引用计数减 - 1
      sub_wref();
    }
  }

  void add_wref() { _weaks++; }

  void sub_wref() {
    if ((--_weaks) == 0) {
      delete_this();
    }
  }
  // 判断管理的对象是否被释放, 若引用计数为 0 返回 false, 否则引用计数+1, 返回
  // true
  bool try_add_ref() {
    if (_uses == 0)
      return false;
    _uses++;
    return true;
  }

  // 引用计数为 0, 销毁管理的资源
  void destroy_resource() noexcept { delete _ptr; }

  // 若引用计数为0,, 销毁引用计数类
  void delete_this() noexcept { delete this; }

  int32_t use_count() { return _uses; }

private:
  // 强引用计数与弱引用计数采用原子操作维护
  // 强引用计数与弱引用计数通过一个类来维护
  std::atomic_int32_t _uses = 1;

  std::atomic_int32_t _weaks = 1;

  T *_ptr;
};

// 基类指针: shared_ptr 与 weak_ptr 分别继承基类指针 Ptr_base
template <class T> struct Ptr_base {
  Ptr_base() = default;
  Ptr_base(const Ptr_base &) = delete;
  Ptr_base &operator=(const Ptr_base &) = delete;

  // 获取裸指针
  T *get() const noexcept { return _ptr; }

  auto use_count() const noexcept -> int32_t {
    return _ref ? _ref->use_count() : 0;
  }

  template <class Ty> void swap(Ptr_base<Ty> &rhs) {
    std::swap(_ptr, rhs._ptr);
    std::swap(_ref, rhs._ref);
  }

private:
  friend class shared_ptr<T>;
  friend class weak_ptr<T>;
  T *_ptr = nullptr;
  RefCount<T> *_ref = nullptr;

  void _init(T *raw_ptr) {
    _ptr = raw_ptr;
    _ref = new RefCount(raw_ptr);
  }

  void add_ref() const {
    if (_ref)
      _ref->add_ref();
  }

  void sub_ref() const {
    if (_ref)
      _ref->sub_ref();
  }

  void add_wref() const {
    if (_ref)
      _ref->add_wref();
  }

  void sub_wref() const {
    if (_ref)
      _ref->sub_wref();
  }

  // 以下需要对裸指针以及引用计数进行修改
  // 主要针对拷贝构造 以及 移动构造带来的指针和引用计数的改变

  template <class Ty> void _copy_ptr_from(const Ptr_base<Ty> &rhs) {
    _ptr = rhs._ptr;
    _ref = rhs._ref;
  }
  // 注意此处: 移动构造中, 从左值做拷贝, 由于移动构造, 注意将原来的左值中的 _ptr
  // 与 _ref 置为 nullptr 类型
  template <class Ty> void _move_construct_from(Ptr_base<Ty> &&rhs) noexcept {
    _copy_ptr_from(rhs);
    rhs._ptr = nullptr;
    rhs._ref = nullptr;
  }

  template <class Ty>
  void _copy_construct_from_shared(const shared_ptr<Ty> &rhs) noexcept {
    rhs.add_ref();
    _copy_ptr_from(rhs);
  }

  template <class Ty>
  void _weakly_construct_from(const Ptr_base<Ty> &rhs) noexcept {
    _copy_ptr_from(rhs);
    add_wref();
  }

  template <class Ty>
  bool _construct_from_weak(const weak_ptr<Ty> &rhs) noexcept {
    if (rhs._ref && rhs._ref->try_add_ref()) {
      _copy_ptr_from(rhs);
      return true;
    }
    return false;
  }
};

// shared_ptr 类 继承自 基类指针
template <typename T> struct shared_ptr : public Ptr_base<T> {
public:
  using Base = Ptr_base<T>;
  shared_ptr() noexcept = default;
  shared_ptr(std::nullptr_t) noexcept {}
  explicit shared_ptr(T *raw_ptr) {
    Base::_init(raw_ptr);
    if constexpr (can_enable_shared<T>) {
      raw_ptr->_weak_this_ = *this;
    }
  }

  // 拷贝构造与拷贝赋值
  shared_ptr(const shared_ptr &rhs) { Base::_copy_construct_from_shared(rhs); }

  // 赋值运算符采用 copy & swap 策略 来做, 统一赋值运算符与移动运算符的实现路径
  shared_ptr &operator=(const shared_ptr &rhs) {
    shared_ptr(rhs).swap(*this); // shared_ptr(rhs) 是一个临时对象
    return *this;
  }

  // 移动构造与移动赋值
  shared_ptr(shared_ptr &&rhs) noexcept {
    Base::_move_construct_from(std::move(rhs));
  }

  shared_ptr &operator=(shared_ptr &&rhs) noexcept {
    shared_ptr(std::move(rhs)).swap(*this);
    return *this;
  }

  // 从 weak_ptr 转换为 shared_ptr
  template <class Ty> shared_ptr(const weak_ptr<Ty> &rhs) noexcept {
    Base::_construct_from_weak(rhs);
  }

  ~shared_ptr() { Base::sub_ref(); }

  // 解引用
  T &operator*() noexcept { return *Base::_ptr; }

  const T &operator*() const noexcept { return *Base::_ptr; }

  // 定义 ->
  T *operator->() { return &*Base::_ptr; }

  const T *operator->() const { return &*Base::_ptr; }

  explicit operator bool() const { return (Base::_ptr != nullptr); }
};

// weak_ptr 类 继承自基类指针
template <typename T> struct weak_ptr : public Ptr_base<T> {
public:
  using Base = Ptr_base<T>;
  weak_ptr() noexcept = default;
  constexpr weak_ptr(std::nullptr_t) noexcept {}

  // 拷贝构造与拷贝赋值 以及从 shared_ptr 的转换
  weak_ptr(const weak_ptr &rhs) { Base::_weakly_construct_from(rhs); }

  weak_ptr &operator=(const weak_ptr &rhs) {
    weak_ptr(rhs).swap(*this);
    return *this;
  }

  weak_ptr(const shared_ptr<T> &rhs) { Base::_weakly_construct_from(rhs); }

  // 移动构造与移动赋值
  weak_ptr(weak_ptr &&rhs) noexcept {
    Base::_move_construct_from(std::move(rhs));
  }

  weak_ptr &operator=(weak_ptr &&rhs) noexcept {
    weak_ptr(std::move(rhs)).swap(*this);
    return *this;
  }

  ~weak_ptr() { Base::sub_wref(); }

  // 返回 管理的对象的 shared_ptr
  shared_ptr<T> lock() const noexcept {
    shared_ptr<T> ret;
    ret._construct_from_weak(*this);
    return ret;
  }

  // 返回 管理的对象是否被释放
  bool expired() const { return Base::_ref->use_count() == 0; }
};

// make 函数
template <typename T, typename... Ts> shared_ptr<T> make_shared(Ts &&...args) {
  return shared_ptr<T>{new T(std::forward<Ts>(args)...)};
}

// enable_shared_from_this 防止 产生多个控制块
template <class T> struct enable_shared_from_this {
  mutable weak_ptr<T> _weak_this_;

protected:
  constexpr enable_shared_from_this() noexcept : _weak_this_() {}

  enable_shared_from_this(const enable_shared_from_this &) noexcept {}

  enable_shared_from_this &operator=(const enable_shared_from_this &) noexcept {
    return *this;
  }

  ~enable_shared_from_this() = default;

public:
  // 返回管理对象的 shared_ptr
  shared_ptr<T> shared_from_this() { return shared_ptr<T>(_weak_this_); }

  // 返回管理 const 对象的 shared_ptr
  shared_ptr<T const> shared_from_this() const {
    return shared_ptr<const T>(_weak_this_);
  }

  friend class shared_ptr<T>;
};

} // namespace smart_ptr

void test_shared() {
  using namespace smart_ptr;
  struct A {
    A(int id) : _id(id) {}
    ~A() { std::cout << "id : " << std::to_string(_id) << "  ~A()\n"; }
    int _id;
  };

  auto s1 = make_shared<A>(1);

  auto s2 = make_shared<A>(2);

  shared_ptr<A> s;
  s1 = std::move(s2);

  s = s1;

  std::cout << s1.use_count() << "\n";
  std::cout << s2.use_count() << "\n";

  s1 = make_shared<A>(3);
}

void test_weak() {
  using namespace smart_ptr;
  struct A;
  struct B;
  struct A {
    A(int id) : _id(id) {}
    ~A() { std::cout << "id : " << std::to_string(_id) << "  ~A()\n"; }
    int _id;
    weak_ptr<B> p;
  };
  struct B {
    weak_ptr<A> p;
    B(int id) : _id(id) {}
    ~B() { std::cout << "id : " << std::to_string(_id) << "  ~B()\n"; }
    int _id;
  };
  {
    auto sa = make_shared<A>(1);
    auto sb = make_shared<B>(2);
    sa->p = sb;
    sb->p = sa;
    auto ss = sa->p.lock(); // shared_ptr
    std::cout << ss.use_count() << "\n";
  }
  weak_ptr<A> weak_a;
  {
    auto sa = make_shared<A>(1);
    weak_a = sa;
  }
  std::cout << weak_a.expired() << "\n"; // 未释放输出 1
}

void test_enable_from() {
  using namespace smart_ptr;

  struct A;
  struct B;
  struct A : enable_shared_from_this<A> {
    A(int id) : _id(id) {}
    ~A() { std::cout << "id : " << std::to_string(_id) << "  ~A()\n"; }
    int _id;
    weak_ptr<B> p;
  };
  struct B : enable_shared_from_this<B> {
    weak_ptr<A> p;
    B(int id) : _id(id) {}
    ~B() { std::cout << "id : " << std::to_string(_id) << "  ~B()\n"; }
    int _id;
  };
  auto sa = make_shared<A>(1);
  auto sb = make_shared<B>(2);
  sa->p = sb;
  sb->p = sa;
  auto ss = sa->p.lock();              // B:2 对象被两个 shared_ptr 指向
  std::cout << ss.use_count() << "\n"; // 输出 2

  auto *raw_ptr = sa.get();
  auto fsp1 = raw_ptr->shared_from_this(); // 返回对象的 shared_ptr 指针
  auto fsp2 = raw_ptr->shared_from_this();
  std::cout << sa.use_count() << "\n"; // fsp1  fsp2   ss  三种
}

int main() {
  test_shared();
  std::cout << "\n\n\n";
  test_weak();
  std::cout << "\n\n\n";
  test_enable_from();
}
