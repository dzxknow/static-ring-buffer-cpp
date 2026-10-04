# Static Ring Buffer (C++20)

A header-only, zero-allocation, ultra-low latency circular ring buffer written in C++20. Designed specifically for deterministic performance in high-frequency trading (HFT) market data processing and real-time execution engines where heap allocation and unpredictable cache misses must be completely eliminated.

## Architectural Highlights

* **Zero Heap Allocations:** Fully stack/static allocated contiguous memory buffer ensuring zero `malloc`/`free` overhead during runtime.
* **Cache-Line Alignment (`alignas(64)`):** Struct and data members are explicitly aligned to 64-byte boundaries to eliminate L1 cache-line splits and prevent false sharing.
* **Power-of-Two Bitwise Wrapping:** Enforces power-of-two capacities via compile-time assertions, replacing modulo division (`%`) with single-cycle bitwise masking (`& MASK`).
* **Move & Copy Semantics:** Overloaded `push()` methods supporting both `const T&` (lvalue) and `T&&` (rvalue move semantics) for zero-copy data transfer.
* **Branch Optimization Hints:** Utilizes C++20 `[[unlikely]]` attributes and `[[nodiscard]]` annotations to optimize compiler branch prediction on hot paths.
* **Benchmarking Isolation:** Includes micro-benchmarking suite utilizing custom inline assembly memory barriers (`asm volatile`) to prevent compiler dead-code elimination under `-O3` optimization flags.

## Project Structure

```text
static-ring-buffer-cpp/
├── include/
│   └── ring_buffer.hpp       # Header-only C++20 circular ring buffer
├── benchmarks/
│   └── main_benchmark.cpp    # Nanosecond-precision microbenchmark suite
├── .gitignore                # Build artifact exclusion
└── README.md                 # Project documentation
