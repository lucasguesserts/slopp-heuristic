#ifndef LARGEST_FIT_FIRST_ALGORITHM_HPP_
#define LARGEST_FIT_FIRST_ALGORITHM_HPP_

#include <vector>

#include "nlohmann/json.hpp"

#include "AllocatedSmallItem.hpp"
#include "BoolCuboid.hpp"
#include "LargeObject.hpp"
#include "SmallItem.hpp"
#include "SmallItemQuantityManager.hpp"
#include "Timer/Timer.hpp"
#include "Vector3D.hpp"

namespace packing {

auto compareSmallItems(const SmallItem & lhs, const SmallItem & rhs) -> bool {
    return lhs.size().volume() < rhs.size().volume();
}

class LargestFitFirstAlgorithm {
public:
    LargestFitFirstAlgorithm(const LargeObject large_object);
    static auto from_json(const nlohmann::json data) -> LargestFitFirstAlgorithm;
    static auto to_json(const LargestFitFirstAlgorithm & algorithm) -> nlohmann::json;

    auto add_item(const SmallItem small_item, const Quantity quantity) -> void;
    auto allocate() -> void;

    auto allocated_items() -> const std::vector<AllocatedSmallItem> & {
        return this->allocated_small_items;
    }
    auto allocation_time() const -> double;

private:
    const LargeObject large_object;
    BoolCuboid space;
    std::vector<SmallItem> small_items;
    SmallItemQuantityManager quantity_manager;
    std::vector<AllocatedSmallItem> allocated_small_items;
    TimerPtr timer;

    auto sort_items_descendig_volume() -> void;
    auto all_space();
    auto is_small_item_available(const SmallItem & small_item) -> bool;
    auto is_item_within_large_object(const SmallItem & small_item, const Vector3D & position) -> bool;
    auto allocate_small_item(const SmallItem & small_item, const Vector3D & position) -> bool;
};

} // namespace packing

#endif
