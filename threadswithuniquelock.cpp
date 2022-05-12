#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

struct criticalSection {
    std::mutex m;
};

// Problematic lock guards with ordering
void fun(criticalSection& a, criticalSection& b) {
    
    std::unique_lock<std::mutex> l1(a.m, std::defer_lock);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // sleep(10);
    std::unique_lock<std::mutex> l2(b.m, std::defer_lock);
    lock(l1,l2);
    cout << "Critical Section with both locks" << endl;    
}

void funny(criticalSection& a, criticalSection& b) {
    std::unique_lock<std::mutex> l1(a.m, std::defer_lock);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // sleep(10);
    std::unique_lock<std::mutex> l2(b.m, std::defer_lock);
    lock(l1,l2);
    
    cout << "Critical Section with both locks" << endl;    
}

int main() {
  
  criticalSection a;
  criticalSection b;
  
//   std::thread t1( fun,a,b);
//   std::thread t2( fun, b,a);

std::thread t1([&]{ fun(a,b);});
std::thread t2([&]{ fun(b,a);});

  t1.join();
  t2.join();
return 0;
}
