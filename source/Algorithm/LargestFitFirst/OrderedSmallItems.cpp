#include "Algorithm/LargestFitFirst/OrderedSmallItems.hpp"

namespace packing {

namespace details {

    auto CompareByVolume::operator()(const SmallItem & lhs, const SmallItem & rhs) const -> bool {
        return lhs.size().volume() > rhs.size().volume();
    }

} // namespace details

} // namespace packing
