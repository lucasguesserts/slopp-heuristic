#ifndef LARGEST_FIT_FIRST_ALGORITHM_HPP_
#define LARGEST_FIT_FIRST_ALGORITHM_HPP_

#include <vector>

#include "nlohmann/json.hpp"

#include "Algorithm/LargestFitFirst/BoolCuboid.hpp"
#include "Geometry/Vector3D.hpp"
#include "LargeObject/BasicLargeObject.hpp"
#include "Timer/Timer.hpp"

#include "SmallItem/BasicSmallItem.hpp"
#include "AllocatedSmallItem/BasicAllocatedSmallItem.hpp"
#include "SmallItem/Container/QuantityManager.hpp"
#include "SmallItem/Container/OrderedSmallItemsByVolume.hpp"

namespace packing {
namespace algorithm {

    class LargestFitFirst {
    public:
        LargestFitFirst(const BasicLargeObject large_object);
        LargestFitFirst(const nlohmann::json & data);

        auto add_item(const BasicSmallItem::Ptr small_item) -> void;
        auto allocate() -> void;

        auto allocated_items() const -> const std::vector<BasicAllocatedSmallItem<BasicSmallItem>> &;
        auto allocation_time() const -> double;

        auto to_json() const -> nlohmann::json;

    private:
        const BasicLargeObject large_object;
        BoolCuboid space;
        OrderedSmallItemsByVolume<BasicSmallItem::Ptr> small_items;
        QuantityManager<BasicSmallItem::Ptr, BasicSmallItem::Hash> quantity_manager;
        std::vector<BasicAllocatedSmallItem<BasicSmallItem>> allocated_small_items;
        TimerPtr timer;

        auto all_space() const;
        auto is_small_item_available(const BasicSmallItem::Ptr & small_item) const -> bool;
        auto is_item_within_large_object(const BasicSmallItem::Ptr & small_item, const Vector3D & position) const -> bool;
        auto allocate_small_item(const BasicSmallItem::Ptr & small_item, const Vector3D & position) -> bool;
    };

} // namespace algorithm

} // namespace packing

#endif
