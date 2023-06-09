#include "LargeObject/Specialization/BasicLargeObject.hpp"

#include <utility>

#include "Geometry/Vector3D.hpp"

namespace packing {

BasicLargeObject::BasicLargeObject(const Vector3D measurement)
    : LargeObjectType()
    , _measurement(std::move(measurement)) {}

} // namespace packing
