#include "SmallItem.hpp"

#include "Size.hpp"
#include <utility>

namespace packing {

SmallItem::SmallItem(const Size size)
    : _size(std::move(size)) {}

} // namespace packing
