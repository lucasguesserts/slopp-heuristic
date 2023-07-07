#ifndef LARGEST_FIT_FIRST_ALGORITHM_V2_HPP_
#define LARGEST_FIT_FIRST_ALGORITHM_V2_HPP_

#include <vector>

#include "nlohmann/json.hpp"

#include "Algorithm/LargestFitFirst/BoolCuboid.hpp"
#include "Algorithm/LargestFitFirst/CornerPointIdentifier.hpp"
#include "Algorithm/LargestFitFirst/PriorityQueueOfVector3D.hpp"
#include "Geometry/Vector3D.hpp"
#include "LargeObject/Specialization/BasicLargeObject.hpp"
#include "Timer/Timer.hpp"

#include "SmallItem/Specialization/SmallItemWithSurface.hpp"
#include "AllocatedSmallItem/Specialization/AllocatedSmallItemWithSurface.hpp"
#include "SmallItem/Container/QuantityManager.hpp"
#include "SmallItem/Container/OrderedSmallItemsByVolume.hpp"

namespace packing {
namespace algorithm {

    class LargestFitFirstV2 {
    public:
        LargestFitFirstV2(const BasicLargeObject large_object);
        LargestFitFirstV2(const nlohmann::json & data);

        auto add_item(const SmallItemWithSurface::Ptr small_item) -> void;
        auto allocate() -> void;

        auto allocated_items() const -> const std::vector<AllocatedSmallItemWithSurface> &;
        auto allocation_time() const -> double;

        auto to_json() const -> nlohmann::json;

    private:
        const BasicLargeObject large_object;
        BoolCuboid space;
        OrderedSmallItemsByVolume<SmallItemWithSurface::Ptr> small_items;
        QuantityManager<SmallItemWithSurface::Ptr, SmallItemWithSurface::Hash> quantity_manager;
        std::vector<AllocatedSmallItemWithSurface> allocated_small_items;
        TimerPtr timer;
        PriorityQueueOfVector3D corner_points;
        CornerPointIdentifier corner_point_identifier;

        auto all_space() const;
        auto is_small_item_available(const SmallItemWithSurface::Ptr & small_item) const -> bool;
        auto is_item_within_large_object(const SmallItemWithSurface::Ptr & small_item, const Vector3D & position) const -> bool;
        auto allocate_small_item(const SmallItemWithSurface::Ptr & small_item, const Vector3D & position) -> bool;
    };

} // namespace algorithm

} // namespace packing

#endif
