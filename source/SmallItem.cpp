#include "SmallItem.hpp"
#include <utility>

#include "Size.hpp"

namespace packing {

SmallItem::SmallItem(const Size size)
    : _size(std::move(size)) {}

auto SmallItem::operator==(const SmallItem & other) const -> bool {
    return this->size() == other.size();
}

} // namespace packing
