#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>

std::atomic<int> shared {0};

void function()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "shared is: " << shared << '\n';
        if (shared.load(std::memory_order_relaxed) > 5)
        {
            std::cout << "Shared is larger than 5 returning\n";
            return;
        }
    }
}

int main()
{
    std::cout << "Hello\n";
    auto thread_object = std::thread(function);
    for (int i = 0; i != 7; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        shared.fetch_add(1, std::memory_order_relaxed);
    }
    thread_object.join();
    std::cout << "Done!\n";
    return 0;
}