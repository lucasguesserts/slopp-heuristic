#include "SmallItem.hpp"

#include <itertools.hpp>
#include <utility>

#include "Geometry/Vector3D.hpp"

namespace packing {

SmallItem::SmallItem(const Vector3D size)
    : _size(std::move(size)) {}

auto SmallItem::operator==(const SmallItem & other) const -> bool {
    return this->size() == other.size();
}

auto SmallItem::surface() const -> Surface {
    auto points = Surface{};
    // bottom
    for (const auto && x : iter::range(static_cast<CoordinateType>(0), this->size().x()))
        for (const auto && y : iter::range(static_cast<CoordinateType>(0), this->size().y())) {
            points.emplace(x, y, -1); // bottom
            points.emplace(x, y, this->size().z()); // top
        }
    // sides
    for (const auto && x : iter::range(static_cast<CoordinateType>(0), this->size().x()))
        for (const auto && z : iter::range(static_cast<CoordinateType>(0), this->size().z())) {
            points.emplace(x, -1, z); // right
            points.emplace(x, this->size().y(), z); // left
        }
    // front and back
    for (const auto && y : iter::range(static_cast<CoordinateType>(0), this->size().y()))
        for (const auto && z : iter::range(static_cast<CoordinateType>(0), this->size().z())) {
            points.emplace(-1, y, z); // back
            points.emplace(this->size().x(), y, z); // front
        }
    return points;
}

} // namespace packing
