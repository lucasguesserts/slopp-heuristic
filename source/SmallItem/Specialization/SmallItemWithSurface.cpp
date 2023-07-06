#include "SmallItem/Specialization/SmallItemWithSurface.hpp"

#include <itertools.hpp>
#include <utility>

#include "Geometry/Surface.hpp"
#include "Geometry/Vector3D.hpp"
#include "SmallItem/BasicSmallItem.hpp"

namespace packing {

SmallItemWithSurface::SmallItemWithSurface(const Vector3D measurement, const Quantity quantity)
    : BasicSmallItem(measurement, quantity) {}

auto SmallItemWithSurface::surface() const -> Surface {
    auto points = Surface{};
    // bottom
    for (const auto && x : iter::range(static_cast<CoordinateType>(0), this->measurement().x()))
        for (const auto && y : iter::range(static_cast<CoordinateType>(0), this->measurement().y())) {
            points.emplace(x, y, -1); // bottom
            points.emplace(x, y, this->measurement().z()); // top
        }
    // sides
    for (const auto && x : iter::range(static_cast<CoordinateType>(0), this->measurement().x()))
        for (const auto && z : iter::range(static_cast<CoordinateType>(0), this->measurement().z())) {
            points.emplace(x, -1, z); // right
            points.emplace(x, this->measurement().y(), z); // left
        }
    // front and back
    for (const auto && y : iter::range(static_cast<CoordinateType>(0), this->measurement().y()))
        for (const auto && z : iter::range(static_cast<CoordinateType>(0), this->measurement().z())) {
            points.emplace(-1, y, z); // back
            points.emplace(this->measurement().x(), y, z); // front
        }
    return points;
}

} // namespace packing
