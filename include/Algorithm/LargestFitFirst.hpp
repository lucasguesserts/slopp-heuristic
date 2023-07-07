#ifndef LARGEST_FIT_FIRST_ALGORITHM_HPP_
#define LARGEST_FIT_FIRST_ALGORITHM_HPP_

#include <vector>

#include "Algorithm/LargestFitFirst/BoolCuboid.hpp"
#include "AllocatedSmallItem/Specialization/BasicAllocatedSmallItem.hpp"
#include "Geometry/Vector3D.hpp"
#include "Input/Specialization/BasicInput.hpp"
#include "LargeObject/Specialization/BasicLargeObject.hpp"
#include "SmallItem/Container/OrderedSmallItemsByVolume.hpp"
#include "SmallItem/Container/QuantityManager.hpp"
#include "SmallItem/Specialization/BasicSmallItem.hpp"
#include "Timer/Timer.hpp"

namespace packing {
namespace algorithm {

    class LargestFitFirst {
    public:
        LargestFitFirst(const BasicInput & data);

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

        LargestFitFirst(const BasicLargeObject large_object);

        auto all_space() const;
        auto is_small_item_available(const BasicSmallItem::Ptr & small_item) const -> bool;
        auto is_item_within_large_object(const BasicSmallItem::Ptr & small_item, const Vector3D & position) const -> bool;
        auto allocate_small_item(const BasicSmallItem::Ptr & small_item, const Vector3D & position) -> bool;
    };

} // namespace algorithm

} // namespace packing

#endif
