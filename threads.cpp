#include <iostream>
#include<thread>
#include<mutex>
using namespace std;

std::mutex m1;

void foo() {
    std::lock_guard<std::mutex> l( m1);
 //   m1.lock();
    std::cout << "function call" << std::endl;
 //   m1.unlock();
}

class functor {
  public:
  functor() {}
  void operator()() {
      std::lock_guard<std::mutex> l(m1);
   //   m1.lock();
      cout << "Functor class" << std::endl;
   //   m1.unlock();
  }
};



int main() {

std::thread t1(foo);
functor f;
std::thread t2(f);
// std::thread t3([]{ m1.lock(); cout << " from lambda" << endl; m1.unlock();});
 std::thread t3([&]{std::lock_guard<std::mutex> l(m1); cout << "from lambda" << endl;});


t1.join();
t2.join();
t3.join();
return 0;

}