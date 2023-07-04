#include "LargeObject/BasicLargeObject.hpp"

#include <utility>

#include "Vector3D.hpp"

namespace packing {

BasicLargeObject::BasicLargeObject(const Vector3D measurement)
    : LargeObjectType()
    , _measurement(std::move(measurement)) {}

} // namespace packing
