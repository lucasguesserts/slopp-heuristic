#include "AllocatedSmallItem.hpp"

#include <itertools.hpp>
#include <utility>

#include "Surface.hpp"
#include "Vector3D.hpp"

namespace packing {

AllocatedSmallItem::AllocatedSmallItem(
    const SmallItem & small_item,
    const Vector3D position)
    : SmallItem(small_item)
    , _position(std::move(position)) {}

auto AllocatedSmallItem::surface() const -> Surface {
    auto points = Surface{};
    // bottom
    for (const auto && x : iter::range(0, this->size().x()))
    for (const auto && y : iter::range(0, this->size().y())) {
        points.insert(this->position() + Vector3D{x, y, -1}); // bottom
        points.insert(this->position() + Vector3D{x, y, this->size().z()}); //top
    }
    // sides
    for (const auto && x : iter::range(0, this->size().x()))
    for (const auto && z : iter::range(0, this->size().z())) {
        points.insert(this->position() + Vector3D{x, -1, z}); // right
        points.insert(this->position() + Vector3D{x, this->size().y(), z}); // left
    }
    // front and back
    for (const auto && y : iter::range(0, this->size().y()))
    for (const auto && z : iter::range(0, this->size().z())) {
        points.insert(this->position() + Vector3D{-1, y, z}); // back
        points.insert(this->position() + Vector3D{this->size().x(), y, z}); // front
    }
    return points;
}

auto AllocatedSmallItem::operator==(const AllocatedSmallItem & other) const -> bool {
    return (this->size() == other.size()) && (this->position() == other.position());
}

} // namespace packing
