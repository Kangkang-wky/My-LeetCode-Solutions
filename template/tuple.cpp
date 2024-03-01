#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

// typename... 表示模板参数类型包
template <typename... Ty> struct Tuple;

// 特化, 空基类
template <> struct Tuple<> {
  template <class... Ty> bool equal(const Tuple<> &rhs) const { return true; }
};

// 模板不定长参数, 通过 typename... Ty2 将一堆类型进行打包操作
// 再通过 Ty2 对其进行解包
template <typename Ty1, typename... Ty2>
struct Tuple<Ty1, Ty2...> : Tuple<Ty2...> {

  // 构造函数如下
  Ty1 val;
  using Base = Tuple<Ty2...>;
  Tuple() {}
  Tuple(Ty1 v, Ty2... args) : val(v), Base(args...) {}

  // 通过以下函数实现对打包类型的数据访问
  Base &getBase() { return *this; }
  const Base &getBase() const { return *this; }

  // 值相等并且解包的参数相等
  template <class... Ty> bool equal(const Tuple<Ty...> &rhs) const {
    return this->val == rhs.val && Base::equal(rhs.getBase());
  }
};

// 模板元编程结合递归 从而实现 tuple 中正确的递归操作
template <int idx, typename _Tuple> struct Tuple_element {
  using Type = typename Tuple_element<idx - 1, typename _Tuple::Base>::Type;
};
template <typename _Tuple> struct Tuple_element<0, _Tuple> {
  using Type = _Tuple;
};

// 实现正确的 Get 访问方法, 并完成类型转换
template <int idx, typename _Tuple> constexpr auto &Get(_Tuple &t) {
  using Type = typename Tuple_element<idx, _Tuple>::Type;
  return static_cast<Type &>(t).val;
}

// 判断是否相等
template <typename... Ty1, typename... Ty2>
bool operator==(const Tuple<Ty1...> &L, const Tuple<Ty2...> &R) {
  return L.equal(R);
}

int main() {
  Tuple<int, std::string> t(7, "test_my_tuple");
  std::vector<Tuple<int, int, double>> vec;
  for (int i = 1; i <= 10; i++) {
    vec.push_back({i, i, 7.0 / i});
  }
  for (auto &x : vec) {
    std::cout << Get<0>(x) << " " << Get<1>(x) << " " << Get<2>(x) << std::endl;
  }

  Tuple<int, int, char, std::string> x(2024, 31, 'a', "student");
  Tuple<int, int, char, std::string> y(2024, 31, 'a', "student");
  std::cout << (x == y) << std::endl;
  Get<3>(y) = '4';
  std::cout << (x == y) << std::endl;
}