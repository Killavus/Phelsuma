#ifndef PHELSUMA_UBO_BUILDER_H
#define PHELSUMA_UBO_BUILDER_H

enum UBOMemoryLayout {
  STD140 = 0
};

class UBOBuilder {
public:
  UBOBuilder(UBOMemoryLayout layout):
    layout(layout), currentOffset(0) {
      start = allocator.allocate(MAX_UBO_SIZE);
    };

  virtual ~UBOBuilder() {
    allocator.release(MAX_UBO_SIZE);
  };

  template<class Type> void add<Type>(Type* type);
  template<class Type> void addArray<Type>(Type *type, size_t arrayLength);
private:
  UBOMemoryLayout layout;
  void *start;
  std::ptrdiff_t currentOffset;

  static StackAllocator allocator;
  static const size_t MAX_UBO_SIZE;
  static const size_t MAX_UBOS_BUILDING;
};
#endif // PHELSUMA_UBO_BUILDER_H
