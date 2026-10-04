#include <cstdio>
#include <cstdint>
#include <chrono>
#include "ring_buffer.hpp"

template <typename T>
inline void doNotOptimizeAway(T&& val) noexcept {
    asm volatile("" : "+r,m"(val) :: "memory");
}

int main() {
    constexpr size_t BUFFER_SIZE= 1024;
    constexpr size_t ITERATIONS = 10'000'000;


    ring_buffer<uint64_t, BUFFER_SIZE> buffer;


    printf("==============================================\n");
    printf("      Static ring buffer low latency          \n");
    printf("==============================================\n");


    //PUSH bench mark:

    auto start = std::chrono::high_resolution_clock::now();

    for(size_t i =0; i < ITERATIONS; ++i){
        if(!buffer.push(i)){

            uint64_t dum = 0;
            while(buffer.pop(dum)) {
                doNotOptimizeAway(dum);

            }
            buffer.push(i);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    //pop benchmark:

    uint64_t val = 0;
    uint64_t checksum = 0;

    auto popof_start = std::chrono::high_resolution_clock::now();

    while(buffer.pop(val)) {
        checksum +=val;
        doNotOptimizeAway(checksum);
    }

    auto endof_pop = std::chrono::high_resolution_clock::now();

    // Latency Calculations
    uint64_t total_push_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double ns_per_push = static_cast<double>(total_push_ns) / ITERATIONS;
    uint64_t total_pop_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(endof_pop - popof_start).count();


    printf("Total Operations     : %lu\n", ITERATIONS);
    printf("Push Execution Time  : %lu ns\n", total_push_ns);
    printf("Average Push Speed   : %.2f ns/op\n", ns_per_push);
    printf("Pop Drain Time       : %lu ns\n", total_pop_ns);
    printf("Checksum Verification: %lu\n\n", checksum);
    printf("==================================================\n");

    return 0;
}