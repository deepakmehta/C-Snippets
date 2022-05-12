#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

using namespace std;

std::mutex t;

class Singleton {

    private:
    static std::atomic<Singleton*> instance_;
    
    Singleton() =default;
    ~Singleton() = default;

    Singleton(const Singleton&)=delete;
    Singleton& operator=(const Singleton&) = delete;

    public:
    static Singleton* getInstance(){
      if (!instance_.load()) {
          std::lock_guard<std::mutex> l1(t);
          if (!instance_.load()){
           Singleton* x = new Singleton();
           instance_.store(x);
          }
      }
      return instance_.load();
    }
};

std::atomic<Singleton*> Singleton::instance_;

int main() {

    std::thread t1([] { for ( int i = 0; i <5;++i){ cout << Singleton::getInstance() << endl;}});
    std::thread t2([] { for ( int i = 0; i <5;++i){ cout << Singleton::getInstance() << endl;}});

    //Singleton* xyz = Singleton::getInstance();
    t1.join();
    t2.join();
    return 0;
}