#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

int shared = 0;
std::mutex shared_mutex;

void function()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(shared_mutex);
        std::cout << "shared is: " << shared << '\n';
        if (shared > 5)
            return;
    }
}

int main()
{
    std::cout << "Hello\n";
    auto thread_object = std::thread(function);
    for (int i = 0; i != 7; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(shared_mutex);
        shared++;
    }
    thread_object.join();
    std::cout << "Done!\n";
    return 0;
}