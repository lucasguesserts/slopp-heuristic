#ifndef ORDERED_SMALL_ITEM_LIST_HPP_
#define ORDERED_SMALL_ITEM_LIST_HPP_

#include <set>

#include "SmallItem/SmallItemType.hpp"

namespace packing {

namespace details {

    template <typename ItemTypePtr>
    struct CompareByVolume {
    public:
        auto operator()(const ItemTypePtr & lhs, const ItemTypePtr & rhs) const -> bool {
            // Notice that it sorts in descending (non-ascending actually) order.
            return lhs->measurement().volume() > rhs->measurement().volume();
        }
    };

} // namespace details

template <typename ItemTypePtr>
using OrderedSmallItemsByVolume = std::multiset<ItemTypePtr, details::CompareByVolume<ItemTypePtr>>;

} // namespace packing

#endif
