#include<iostream>
#include<chrono>
std::chrono::time_point<std::chrono::steady_clock> base = std::chrono::steady_clock::now();

extern "C" float get_elapsed_time(){
std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
std::chrono::duration<float,std::ratio<1>> time_elapsed = std::chrono::duration_cast<std::chrono::duration<float,std::ratio<1>>>(start - base);
 return time_elapsed.count();
}
