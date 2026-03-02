#pragma once

#include <cstddef>
#include <memory_resource>
#include <vector>

namespace sbx {
template <typename T, std::size_t n_elems>
struct MonotonicBufferMr {
    inline static constexpr std::size_t n_bytes{sizeof(T) * n_elems};

    MonotonicBufferMr()
        : mr{&buffer, n_bytes, std::pmr::null_memory_resource()} {}

    MonotonicBufferMr(MonotonicBufferMr const&) = delete;
    MonotonicBufferMr(MonotonicBufferMr&&) = delete;

    auto& operator=(MonotonicBufferMr const&) = delete;
    auto& operator=(MonotonicBufferMr&&) = delete;

    auto allocator() -> std::pmr::polymorphic_allocator<T> { return {&mr}; }

    std::pmr::monotonic_buffer_resource mr;
  private:
    alignas(T) std::byte buffer[n_bytes];
};

template <typename T, std::size_t n_elems>
struct StaticPmrVector {
    StaticPmrVector()
        : vec{memory.allocator()} {
        vec.reserve(n_elems);
    }

    StaticPmrVector(StaticPmrVector const&) = delete;
    StaticPmrVector(StaticPmrVector&&) = delete;

    auto& operator=(StaticPmrVector const&) = delete;
    auto& operator=(StaticPmrVector&&) = delete;

    sbx::MonotonicBufferMr<T, n_elems> memory{};
    std::pmr::vector<T> vec;
};

}
