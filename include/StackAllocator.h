#ifndef PHELSUMA_STACK_ALLOCATOR_H
#define PHELSUMA_STACK_ALLOCATOR_H
#include <cstddef>
#include <cstdint>

class StackAllocator {
  public:
    StackAllocator(size_t capacity): head(0), capacity(capacity) {
      start = static_cast<void*>(new uint8_t[capacity]);
    }

    void* allocate(size_t bytes);
    void release(size_t bytes);
  private:
    std::ptrdiff_t head;
    size_t capacity;
    void* start;
};
#endif // PHELSUMA_STACK_ALLOCATOR_H
