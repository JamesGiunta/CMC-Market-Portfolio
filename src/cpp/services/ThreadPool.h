#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
using namespace std;

class ThreadPool {
  public:
    ThreadPool(size_t numThreads = std::thread::hardware_concurrency()) {
        for (size_t i = 0; i < numThreads; i++) {
            threads.emplace_back([this] {
                while (true) {
                    std::function<void()> task; {
                        std::unique_lock<std::mutex> lock(mutex);
                        conditionVariable.wait(lock, [this] {
                            return !tasks.empty() || stopFlag;
                        });

                        if (stopFlag && tasks.empty()) {
                            return;
                        }

                        task = std::move(tasks.front());
                        tasks.pop();

                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        unique_lock<std::mutex> lock(mutex);
        stopFlag = true;
        conditionVariable.notify_all();

        for (thread &thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

    void enqueue(std::function<void()> task) {
        {
            std::unique_lock<std::mutex> lock(mutex);
            tasks.emplace(std::move(task));
        }
        conditionVariable.notify_one();
    }

    private:
        vector<thread> threads;
        mutable std::mutex mutex;
        std::condition_variable conditionVariable;
        bool stopFlag = false;
        queue<std::function<void()>> tasks;
};

