#include "AllocatedSmallItem.hpp"

#include <algorithm>
#include <iterator>
#include <itertools.hpp>
#include <utility>

#include "Geometry/Surface.hpp"
#include "Geometry/Vector3D.hpp"

namespace packing {

AllocatedSmallItem::AllocatedSmallItem(
    const SmallItem & small_item,
    const Vector3D position)
    : SmallItem(small_item)
    , _position(std::move(position)) {}

auto AllocatedSmallItem::surface() const -> Surface {
    const auto small_item_surface = this->SmallItem::surface();
    auto points = Surface{};
    std::transform(
        small_item_surface.cbegin(),
        small_item_surface.cend(),
        std::inserter(points, points.end()),
        [this](const auto & point) {
            return point + this->position();
        });
    return points;
}

auto AllocatedSmallItem::operator==(const AllocatedSmallItem & other) const -> bool {
    return (this->size() == other.size()) && (this->position() == other.position());
}

} // namespace packing
