#include "StackAllocator.h"

void* StackAllocator::allocate(size_t bytes) {
  void* mem = (start + head);
  head += bytes;
  return mem;
}

void StackAllocator::release(size_t bytes) {
  head -= bytes;
}
