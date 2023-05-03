#include "LargeObject.hpp"

#include <utility>

#include "Vector3D.hpp"

namespace packing {

LargeObject::LargeObject(const Vector3D size)
    : _size(std::move(size)) {}

} // namespace packing
