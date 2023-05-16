#include "Vector3D.hpp"

#include <utility>

namespace packing {

Vector3D::Vector3D(const CoordinateType x, const CoordinateType y, const CoordinateType z)
    : _x(std::move(x))
    , _y(std::move(y))
    , _z(std::move(z)) {}

auto Vector3D::operator==(const Vector3D & other) const -> bool {
    return (this->x() == other.x()) && (this->y() == other.y()) && (this->z() == other.z());
}

auto operator<(const Vector3D & lhs, const Vector3D & rhs) -> bool {
    if (lhs.x() < rhs.x()) {
        return true;
    } else if (lhs.x() > rhs.x()) {
        return false;
    } else if (lhs.y() < rhs.y()) {
        return true;
    } else if (lhs.y() > rhs.y()) {
        return false;
    } else {
        return lhs.z() < rhs.z();
    }
}

} // namespace packing
