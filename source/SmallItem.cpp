#include "SmallItem.hpp"
#include <utility>

#include "Size.hpp"

namespace packing {

SmallItem::SmallItem(const Size size)
    : _size(std::move(size)) {}

} // namespace packing
