#ifndef CORNER_POINT_IDENTIFIER_HPP_
#define CORNER_POINT_IDENTIFIER_HPP_

#include "BoolCuboid.hpp"
#include "Vector3D.hpp"

namespace packing {

class CornerPointIdentifier {
public:
    CornerPointIdentifier(const BoolCuboid & space);
    auto is_corner_point(const Vector3D & point) const -> bool;

private:
    const BoolCuboid & space;

    auto is_occupied_or_inexistent_x(const Vector3D & point) const -> bool;
    auto is_occupied_or_inexistent_y(const Vector3D & point) const -> bool;
    auto is_occupied_or_inexistent_z(const Vector3D & point) const -> bool;
};

} // namespace packing

#endif
