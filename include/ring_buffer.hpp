#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

template <typename T, size_t Capacity>
class alignas(64) ring_buffer {
    static_assert((Capacity & (Capacity - 1)) == 0, "Capacity should be power of 2");
    static_assert(Capacity > 0, "Capacity must be greater than zero!");

private:
    alignas(64) T data_[Capacity];
    alignas(64) size_t head_ = 0;
    alignas(64) size_t tail_ = 0;
    alignas(64) size_t count_ = 0;

    static constexpr size_t MASK = Capacity - 1;

public:
    constexpr ring_buffer() noexcept = default;

    // 1. Lvalue Push (Copy Semantics)
    [[nodiscard]] inline bool push(const T& item) noexcept {
        if (count_ == Capacity) [[unlikely]] {
            return false; // Buffer is full
        }

        data_[tail_] = item;
        tail_ = (tail_ + 1) & MASK;
        count_++;
        return true;
    }

    // Rvalue push (move Semantics - Zero Copy)
    [[nodiscard]] inline bool push(T&& item) noexcept {
        if (count_ == Capacity) [[unlikely]] {
            return false; // Buffer is full
        }

        data_[tail_] = std::move(item);
        tail_ = (tail_ + 1) & MASK;
        count_++;
        return true;
    }
    // pop (with Move avoid unecessary copies)
    [[nodiscard]] inline bool pop(T& item) noexcept {
        if(count_ == 0) [[unlikely]] {
            return false;
        }
        item = std::move(data_[head_]);
        head_ = (head_ + 1) & MASK;
        count_--;
        return true;
    }

    // CURRENT NUM OF ELEMENT STORED ELEMENTS
    [[nodiscard]] inline size_t size() const noexcept {
        return count_;
    }

    //returns true if buffer has zero elements;

    [[nodiscard]] inline bool empty() const noexcept {
        return count_ == 0;
    }

    // return true if buffer is fulll;

    [[nodiscard]] inline bool full() const noexcept {
        return count_ == Capacity;
    }

    // return maximum capacity
    [[nodiscard]] inline constexpr size_t capacity() const noexcept {
        return Capacity;
    }
};