#include "SmallItem.hpp"
#include <utility>

#include "Vector3D.hpp"

namespace packing {

SmallItem::SmallItem(const Vector3D size)
    : _size(std::move(size)) {}

auto SmallItem::operator==(const SmallItem & other) const -> bool {
    return this->size() == other.size();
}

} // namespace packing
