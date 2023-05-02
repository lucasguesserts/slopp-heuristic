#include "AllocatedSmallItem.hpp"

#include <utility>

#include "Vector3D.hpp"

namespace packing {

AllocatedSmallItem::AllocatedSmallItem(
    const SmallItem & small_item,
    const Vector3D position)
    : SmallItem(small_item)
    , _position(std::move(position)) {}

auto AllocatedSmallItem::operator==(const AllocatedSmallItem & other) const -> bool {
    return (this->size() == other.size()) && (this->position() == other.position());
}

} // namespace packing
