#pragma once
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

class ThreadPool {
public:
    ThreadPool(size_t num_threads = std::thread::hardware_concurrency());
    ~ThreadPool();
    void enqueue(std::function<void()> task);

private:
    std::vector<std::thread> threads;
    mutable std::mutex queueMutex;
    std::condition_variable conditionVariable;
    bool stopFlag = false;
    std::queue<std::function<void()>> tasks;
};