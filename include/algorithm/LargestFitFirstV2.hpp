#ifndef LARGEST_FIT_FIRST_ALGORITHM_V2_HPP_
#define LARGEST_FIT_FIRST_ALGORITHM_V2_HPP_

#include <vector>

#include "nlohmann/json.hpp"

#include "AllocatedSmallItem.hpp"
#include "BoolCuboid.hpp"
#include "CornerPointIdentifier.hpp"
#include "LargeObject.hpp"
#include "PriorityQueueOfVector3D.hpp"
#include "SmallItem.hpp"
#include "SmallItemQuantityManager.hpp"
#include "Timer/Timer.hpp"
#include "Vector3D.hpp"

namespace packing {
namespace algorithm {

    class LargestFitFirstV2 {
    public:
        LargestFitFirstV2(const LargeObject large_object);
        LargestFitFirstV2(const nlohmann::json & data);

        auto add_item(const SmallItem small_item, const Quantity quantity) -> void;
        auto allocate() -> void;

        auto allocated_items() const -> const std::vector<AllocatedSmallItem> &;
        auto allocation_time() const -> double;

        auto to_json() const -> nlohmann::json;

    private:
        const LargeObject large_object;
        BoolCuboid space;
        std::vector<SmallItem> small_items;
        SmallItemQuantityManager quantity_manager;
        std::vector<AllocatedSmallItem> allocated_small_items;
        TimerPtr timer;
        PriorityQueueOfVector3D corner_points;
        CornerPointIdentifier corner_point_identifier;


        auto sort_items_descendig_volume() -> void;
        auto all_space() const;
        auto is_small_item_available(const SmallItem & small_item) const -> bool;
        auto is_item_within_large_object(const SmallItem & small_item, const Vector3D & position) const -> bool;
        auto allocate_small_item(const SmallItem & small_item, const Vector3D & position) -> bool;

        static auto compareSmallItems(const SmallItem & lhs, const SmallItem & rhs) -> bool;
    };

} // namespace algorithm

} // namespace packing

#endif
