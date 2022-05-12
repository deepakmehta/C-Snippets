#include <iostream>
#include <atomic>
#include <thread>
using namespace std;

class SpinLock {
 std::atomic_flag f;
 public:
  SpinLock(): f(ATOMIC_FLAG_INIT){}

 void lock( ) {while(!f.test_and_set());}

 void unlock() { f.clear();}
};

SpinLock s;

void f() {
    s.lock();
    cout << "in critical section" << endl;
    s.unlock();
}

int main(){
    std::thread t1([]{for ( int i=0; i <5;++i) f(); });
    std::thread t2([]{for ( int i=0; i <5;++i) f(); });

    t1.join();
    t2.join();
}