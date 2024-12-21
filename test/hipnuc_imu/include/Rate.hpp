#pragma once
/**
 * 控制循环的频率
*/
#include <chrono>
#include <thread>

class Rate {
public:
    Rate(double frequency);

    void sleep();

private:
    std::chrono::duration<double> period_;
    std::chrono::steady_clock::time_point last_time_;
};

// Constructor implementation
Rate::Rate(double frequency) : period_(std::chrono::duration<double>(1.0 / frequency)) {
    last_time_ = std::chrono::steady_clock::now();
}

// Member function implementation
void Rate::sleep() {
    auto current_time = std::chrono::steady_clock::now();
    auto elapsed = current_time - last_time_;
    auto sleep_time = period_ - elapsed;

    if (sleep_time > std::chrono::duration<double>(0)) {
        std::this_thread::sleep_for(sleep_time);
    }

    last_time_ = std::chrono::steady_clock::now();
}