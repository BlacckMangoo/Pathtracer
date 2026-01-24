#pragma once
#include <chrono>
#include <iostream>

using namespace std::chrono;
class Profiler {

    steady_clock::time_point startTime{};
    steady_clock::time_point endTime{};
public:
    Profiler() {
        startTime = steady_clock::now();
    }

    ~Profiler() {
        endTime = steady_clock::now();
        std::cout << "ElapsedTime:" << duration_cast<milliseconds>(endTime - startTime).count();
    }


};