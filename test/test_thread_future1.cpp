#include <future>
#include <iostream>
#include <thread>

using namespace std;

int main(int argc, char const *argv[]) {

  thread t([] { cout << "hello" << endl; });
  t.join();

  return 0;
}
