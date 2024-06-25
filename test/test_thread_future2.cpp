#include <future>
#include <iostream>
#include <thread>

using namespace std;

int main(int argc, char const *argv[]) {

  auto f = async([] { cout << "hello" << endl; });
  f.wait();

  return 0;
}
