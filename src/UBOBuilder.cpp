#include "StackAllocator.h"

const size_t UBOBuilder::MAX_UBOS_BUILDING = 8;
const size_t UBOBuilder::MAX_UBO_SIZE = 16 * 1024;

StackAllocator UBOBuilder::allocator = StackAllocator(MAX_UBOS_BUILDING * MAX_UBO_SIZE);

template<> void UBOBuilder::add<uint32_t>(uint32_t value) {
  start[currentOffset] = value;
  currentOffset += sizeof(uint32_t);
}

template<> void UBOBuilder::add<int32_t>(int32_t value) {
  start[currentOffset] = value;
  currentOffset += sizeof(int32_t);
}

template<> void UBOBuilder::add<bool>(bool value) {
  start[currentOffset] = value;
  currentOffset += 4;
}

template<> void UBOBuilder::add<Vector4>(const Vector4& value) {

}

template<> void UBOBuilder::add<Vector3>(const Vector3& value) {

}

template<> void UBOBuilder::add<Vector2>(const Vector2& value) {

}

template<> void UBOBuilder::add<Matrix4>(const Matrix4& value) {

}

template<> void UBOBuilder::add<Matrix3>(const Matrix3& value) {

}
