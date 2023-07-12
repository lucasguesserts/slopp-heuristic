#include "Algorithm/LargestFitFirstV2.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>

#include "nlohmann/json.hpp"
#include <itertools.hpp>

#include "Algorithm/LargestFitFirst/BoolCuboid.hpp"
#include "AllocatedSmallItem/Specialization/BasicAllocatedSmallItem.hpp"
#include "Geometry/Vector3D.hpp"
#include "LargeObject/Specialization/BasicLargeObject.hpp"
#include "SmallItem/Specialization/SmallItemWithSurface.hpp"
#include "Timer/Timer.hpp"
#include "Timer/UserTimer.hpp"

using nlohmann::json;
using std::string;
using OrderedJson = nlohmann::ordered_json;

namespace packing {

namespace algorithm {

    LargestFitFirstV2::LargestFitFirstV2(const BasicLargeObject large_object)
        : LargestFitFirst{large_object}
        , corner_point_identifier(this->space) {}

    LargestFitFirstV2::LargestFitFirstV2(BasicInput<SmallItemWithSurface> & data)
        : LargestFitFirstV2{data.large_object()} {
        // small items
        for (const auto & small_item : data.small_items()) {
            this->add_item(small_item);
        }
        this->compare_small_items = [](const std::shared_ptr<SmallItemWithSurface> & lhs, const std::shared_ptr<SmallItemWithSurface> & rhs) {
            return lhs->measurement().volume() > rhs->measurement().volume();
        };
        return;
    }

    auto LargestFitFirstV2::allocate() -> void {
        this->timer->start();
        std::sort(this->small_items.begin(), this->small_items.end(), this->compare_small_items);
        this->corner_points.emplace(0, 0, 0);
        while (!this->corner_points.empty()) {
            const auto point_to_allocate = this->corner_points.top();
            const auto x = point_to_allocate.x();
            const auto y = point_to_allocate.y();
            const auto z = point_to_allocate.z();
            this->corner_points.pop();
            if (this->space.is_free(x, y, z)) {
                for (const auto & small_item : this->small_items) {
                    if (!this->is_item_within_large_object(small_item, {x, y, z})) continue;
                    if (!this->is_small_item_available(small_item)) continue;
                    const auto sucessfully_added = this->allocate_small_item(small_item, {x, y, z});
                    if (sucessfully_added) {
                        // scan the surface of the allocated item for new corner points
                        const auto & allocated_small_item = this->allocated_small_items.back();
                        for (const auto & point : allocated_small_item.surface()) {
                            if (this->corner_point_identifier.is_corner_point(point)) {
                                this->corner_points.emplace(point);
                            }
                        }
                        break;
                    }
                }
            }
        }
        this->timer->stop();
        return;
    }

} // namespace algorithm

} // namespace packing
