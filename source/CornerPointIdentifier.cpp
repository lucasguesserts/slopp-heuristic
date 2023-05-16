#include "CornerPointIdentifier.hpp"
#include "Vector3D.hpp"

namespace packing {

CornerPointIdentifier::CornerPointIdentifier(const BoolCuboid & space)
    : space(space) {}

auto CornerPointIdentifier::is_corner_point(const Vector3D & point) const -> bool {
    if (space.is_occupied(point.x(), point.y(), point.z())) {
        return false;
    }
    const auto x_condition = is_occupied_or_inexistent_x(Vector3D{point.x(), point.y(), point.z()});
    const auto y_condition = is_occupied_or_inexistent_y(Vector3D{point.x(), point.y(), point.z()});
    const auto z_condition = is_occupied_or_inexistent_z(Vector3D{point.x(), point.y(), point.z()});
    return x_condition && y_condition && z_condition;
}

auto CornerPointIdentifier::is_occupied_or_inexistent_x(const Vector3D & point) const -> bool {
    if ((point.x() == 0)) {
        return true;
    } else {
        return space.is_occupied(point.x() - 1, point.y(), point.z());
    }
}

auto CornerPointIdentifier::is_occupied_or_inexistent_y(const Vector3D & point) const -> bool {
    if ((point.y() == 0)) {
        return true;
    } else {
        return space.is_occupied(point.x(), point.y() - 1, point.z());
    }
}

auto CornerPointIdentifier::is_occupied_or_inexistent_z(const Vector3D & point) const -> bool {
    if ((point.z() == 0)) {
        return true;
    } else {
        return space.is_occupied(point.x(), point.y(), point.z() - 1);
    }
}

} // namespace packing
