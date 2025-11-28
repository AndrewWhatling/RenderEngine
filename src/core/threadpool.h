#pragma once

#include <vector>
#include <thread>
#include <queue>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <functional>

// definition of threadPool class
class threadPool {
public:
    threadPool(size_t num_threads);
    ~threadPool();

    // Submit a job to the pool 
    void queue(std::function<void()> job);
    
    // Wait for all jobs to finish
    void wait();

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop{false};
    std::atomic<int> working_threads{0};

    void worker_thread();
};

// destructor for threadPool, finalising all jobs and cleanly exiting the given jobs
inline threadPool::~threadPool() {
    stop = true;
    condition.notify_all();
    for (auto &thread : workers) 
        thread.join();
}
// queue a worker up for a new job
inline void threadPool::queue(std::function<void()> job) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        tasks.push(std::move(job));
    }
    condition.notify_one();
}
// wait for a new job to open up
inline void threadPool::wait() {
    while (true) {
        if (tasks.empty() && working_threads == 0)
            break;
        std::this_thread::yield();
    }
}
// core logic that each thread runs inside pool
inline void threadPool::worker_thread() {
    while (!stop) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            condition.wait(lock, [this] {return stop || !tasks.empty(); });
            if (stop && tasks.empty()) return;

            job = std::move(tasks.front());
            tasks.pop();
            working_threads++;
        }
        job();
        working_threads--;
    }
}
// Initialise workers
inline threadPool::threadPool(size_t num_threads) {
    for (size_t i = 0; i < num_threads; ++i) {
        workers.emplace_back([this]() { this->worker_thread(); });
    }
}


