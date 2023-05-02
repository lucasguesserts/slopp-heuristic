#ifndef LARGEST_FIT_FIRST_ALGORITHM_HPP_
#define LARGEST_FIT_FIRST_ALGORITHM_HPP_

#include <vector>

#include "Vector3D.hpp"
#include "BoolCuboid.hpp"
#include "LargeObject.hpp"
#include "SmallItem.hpp"
#include "AllocatedSmallItem.hpp"
#include "SmallItemQuantityManager.hpp"

namespace packing {

auto compareSmallItems(const SmallItem & lhs, const SmallItem & rhs) -> bool {
    return lhs.size().volume() < rhs.size().volume();
}

class LargestFitFirstAlgorithm {
public:
    LargestFitFirstAlgorithm(const LargeObject large_object);
    auto add_item(const SmallItem small_item, const Quantity quantity) -> void;
    auto allocate() -> void;

    auto allocated_items() -> const std::vector<AllocatedSmallItem> & {
        return this->allocated_small_items;
    }

private:
    const LargeObject large_object;
    BoolCuboid space;
    std::vector<SmallItem> small_items;
    SmallItemQuantityManager quantity_manager;
    std::vector<AllocatedSmallItem> allocated_small_items;

    auto sort_items_descendig_volume() -> void;
    auto all_space();
    auto is_small_item_available(const SmallItem & small_item) -> bool;
    auto allocate_small_item(const SmallItem & small_item, const Vector3D & position) -> bool;
};

} // namespace packing

#endif
