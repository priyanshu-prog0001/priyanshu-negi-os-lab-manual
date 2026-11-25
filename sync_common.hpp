// Helpers for the synchronization programs (4, 5 and 6)
#pragma once
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <sstream>

// Small counting-semaphore class (portable C++11 replacement for sem_t)
class Semaphore {
    std::mutex m_;
    std::condition_variable cv_;
    int count_;
public:
    explicit Semaphore(int count = 0) : count_(count) {}
    void wait() {                       // P operation
        std::unique_lock<std::mutex> lk(m_);
        cv_.wait(lk, [this] { return count_ > 0; });
        --count_;
    }
    void post() {                       // V operation
        { std::lock_guard<std::mutex> lk(m_); ++count_; }
        cv_.notify_one();
    }
};

// Thread-safe printing: SafePrint() << "text" << value << "\n";
// The whole line is written at once, so lines from different threads never mix.
class SafePrint {
    std::ostringstream ss_;
    static std::mutex &lock() { static std::mutex m; return m; }
public:
    template <typename T>
    SafePrint &operator<<(const T &v) { ss_ << v; return *this; }
    ~SafePrint() {
        std::lock_guard<std::mutex> lk(lock());
        std::cout << ss_.str() << std::flush;
    }
};
