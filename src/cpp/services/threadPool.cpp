#include "threadPool.h"
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

ThreadPool::ThreadPool(size_t numThreads) {
    for (size_t i = 0; i < numThreads; i++) {
        threads.emplace_back([this] {
            while (true) {
                std::function<void()> task; {
                    std::unique_lock<std::mutex> lock(queueMutex);
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

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stopFlag = true;
    }
    conditionVariable.notify_all();
    for (std::thread &thread : threads) {
        thread.join();
    }
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.emplace(std::move(task));
    }
    conditionVariable.notify_one();
}