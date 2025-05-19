#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
using namespace std;

class ThreadPool {
  public:
    ThreadPool(size_t numThreads = std::thread::hardware_concurrency()) {};
    ~ThreadPool() {}
    void enqueue(std::function<void()> task) {}

    private:
        vector<thread> threads;
        mutable std::mutex mutex;
        std::condition_variable conditionVariable;
        bool stopFlag = false;
        queue<std::function<void()>> tasks;
};