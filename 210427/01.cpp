#include <algorithm>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <vector>

namespace hse::cpp {

// Keyword mutable usage example
class Object {
public:
    int type() const {
        std::scoped_lock<std::mutex> lock(type_mutex);
        return type_id;
    }

private:
    mutable std::mutex type_mutex;
    int type_id;
};

class Latch {
public:
    explicit Latch(int remaining) : remaining_(remaining) {
    }

    void wait() {
        std::unique_lock<std::mutex> lock(remaining_mutex_);
        --remaining_;
        remaining_changed_.notify_all();
        remaining_changed_.wait(lock, [&r = remaining_] { return r <= 0; });
    }

private:
    int remaining_;
    std::mutex remaining_mutex_;
    std::condition_variable remaining_changed_;
};

}  // namespace hse::cpp

int main(int argc, char *argv[]) {
    using namespace hse::cpp;

    std::cout << "Sequential" << std::endl;
    for (int i = 1; i < argc; ++i) {
        std::cout << i << ": " << argv[i] << std::endl;
    }

    std::cout << "Parallel" << std::endl;
    {
        std::vector<std::thread> threads;
        for (int i = 1; i < argc; ++i) {
            threads.emplace_back(
                [i, &argv] { std::cout << i << ": " << argv[i] << std::endl; });
        }

        for (auto &thread : threads) {
            thread.join();
        }
    }

    std::cout << "Parallel latched" << std::endl;
    {
        // std::mutex cout_mutex;
        Latch latch(argc - 1);
        std::vector<std::thread> threads;
        for (int i = 1; i < argc; ++i) {
            threads.emplace_back([i, &argv, &latch /*, &cout_mutex*/] {
                latch.wait();
                // Single thread deadlock example
                // std::unique_lock<std::mutex> lock(cout_mutex);
                // std::unique_lock<std::mutex> deadlock(cout_mutex);
                std::cout << i << ": " << argv[i] << std::endl;
            });
        }

        for (auto &thread : threads) {
            thread.join();
        }
    }

    std::cout << "Parallel latched for thread sanitizer" << std::endl;
    {
        std::mutex cout_mutex;
        Latch latch(argc - 1);
        std::vector<std::thread> threads;
        for (int i = 1; i < argc; ++i) {
            threads.emplace_back([i, &argv, &latch, &cout_mutex] {
                // std::unique_lock<std::mutex> lock(cout_mutex); // deadlock
                latch.wait();
                std::unique_lock<std::mutex> lock(cout_mutex);
                std::cout << i << ": " << argv[i] << std::endl;
            });
        }

        for (auto &thread : threads) {
            thread.join();
        }
    }

    std::cout << "Two thread possible deadlock" << std::endl;
    {
        std::mutex m1;
        std::mutex m2;

        std::thread t1([&m1, &m2] {
            std::unique_lock<std::mutex> l1(m1);
            std::unique_lock<std::mutex> l2(m2);
            std::cout << "Tread 1" << std::endl;
        });

        std::thread t2([&m1, &m2] {
            std::unique_lock<std::mutex> l2(m2);
            std::unique_lock<std::mutex> l1(m1);
            std::cout << "Tread 2" << std::endl;
        });

        t1.join();
        t2.join();
    }

    std::cout << "Two thread no deadlock" << std::endl;
    {
        std::mutex m1;
        std::mutex m2;

        std::thread t1([&m1, &m2] {
            std::scoped_lock lock(m1, m2);
            std::cout << "Tread 1" << std::endl;
        });

        std::thread t2([&m1, &m2] {
            std::scoped_lock lock(m2, m1);
            std::cout << "Tread 2" << std::endl;
        });

        t1.join();
        t2.join();
    }

    return 0;
}