# Static Ring Buffer (C++20)

A zero-allocation, header-only, ultra-low latency circular ring buffer written in C++20 for high-frequency trading and low-latency systems.

## Features
- **Zero Heap Allocations:** Stack/static allocated contiguous memory.
- **Cache Line Alignment:** Aligned to 64 bytes (`alignas(64)`) to eliminate L1 cache-line splits.
- **Bitwise Modulo:** Requires power-of-two capacity, replacing slow `%` division with `& MASK` bitwise masking.
- **Move & Copy Semantics:** Perfect forwarding support via `T&&` and `const T&` overloads.
- **Compile-Time Safety:** `static_assert` enforces power-of-two capacity at build time.

## Build & Run Benchmark

```bash
g++ -O3 -march=native -flto -std=c++20 benchmarks/main_benchmark.cpp -I include -o benchmark
./benchmark