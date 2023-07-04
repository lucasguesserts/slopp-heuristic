#ifndef ORDERED_SMALL_ITEMS_HPP_
#define ORDERED_SMALL_ITEMS_HPP_

#include <set>

#include "SmallItem.hpp"

namespace packing {

namespace details {

    struct CompareByVolume {
    public:
        auto operator()(const SmallItem & lhs, const SmallItem & rhs) const -> bool;
    };

} // namespace details

using OrderedSmallItems = std::multiset<SmallItem, details::CompareByVolume>;

} // namespace packing

#endif
