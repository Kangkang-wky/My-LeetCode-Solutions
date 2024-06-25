#include <chrono>
#include <future>
#include <iostream>

// 定义一个异步任务
std::string fetchDataFromDB(std::string query) {
  // 模拟一个异步任务，比如从数据库中获取数据
  std::this_thread::sleep_for(std::chrono::seconds(5));
  return "Data: " + query;
}

int main() {
  // 使用 std::async 异步调用 fetchDataFromDB
  std::future<std::string> resultFromDB =
      std::async(std::launch::async, fetchDataFromDB, "Data");

  // 在主线程中做其他事情
  std::cout << "Doing something else..." << std::endl;

  // 从 future 对象中获取数据
  // 异步操作返回一个 future 对象, future 对象完成调用
  std::string dbData = resultFromDB.get();
  std::cout << dbData << std::endl;

  return 0;
}