#include "Algorithm/LargestFitFirstV2.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>

#include "Geometry/Vector3D.hpp"
#include "SmallItem/Specialization/SmallItemWithSurface.hpp"
#include "nlohmann/json.hpp"
#include <itertools.hpp>

#include "Algorithm/LargestFitFirst/BoolCuboid.hpp"
#include "AllocatedSmallItem/Specialization/BasicAllocatedSmallItem.hpp"
#include "LargeObject/BasicLargeObject.hpp"
#include "Timer/Timer.hpp"
#include "Timer/UserTimer.hpp"

using nlohmann::json;
using std::string;
using OrderedJson = nlohmann::ordered_json;

namespace packing {

namespace algorithm {

    LargestFitFirstV2::LargestFitFirstV2(const BasicLargeObject large_object)
        : large_object(large_object)
        , space(large_object.measurement())
        , timer(UserTimer::make())
        , corner_point_identifier(this->space) {}

    LargestFitFirstV2::LargestFitFirstV2(const json & data)
        : LargestFitFirstV2{Vector3D{
            data.at("large_object").at("length").get<CoordinateType>(),
            data.at("large_object").at("width").get<CoordinateType>(),
            data.at("large_object").at("height").get<CoordinateType>()}} {
        // small items
        const auto small_items_data = data.at("small_items");
        for (const auto & small_item_data : data.at("small_items")) {
            const auto small_item = std::make_shared<SmallItemWithSurface>(
                Vector3D{
                    small_item_data.at("length").get<CoordinateType>(),
                    small_item_data.at("width").get<CoordinateType>(),
                    small_item_data.at("height").get<CoordinateType>()},
                small_item_data.at("quantity").get<Quantity>());
            this->add_item(small_item);
        }
        return;
    }

    auto LargestFitFirstV2::to_json() const -> json {
        auto output = OrderedJson{};
        // metadata
        output["type"] = "output";
        output["version"] = "0.2.0";
        // large object
        auto large_object_data = OrderedJson{};
        large_object_data["length"] = this->large_object.measurement().x();
        large_object_data["width"] = this->large_object.measurement().y();
        large_object_data["height"] = this->large_object.measurement().z();
        output["large_object"] = large_object_data;
        // small items
        auto small_items_data = json::array();
        for (const auto & allocated_small_item : this->allocated_small_items) {
            auto allocated_item_data = OrderedJson{};
            allocated_item_data["length"] = allocated_small_item.type().measurement().x();
            allocated_item_data["width"] = allocated_small_item.type().measurement().y();
            allocated_item_data["height"] = allocated_small_item.type().measurement().z();
            allocated_item_data["x"] = allocated_small_item.position().x();
            allocated_item_data["y"] = allocated_small_item.position().y();
            allocated_item_data["z"] = allocated_small_item.position().z();
            small_items_data.emplace_back(std::move(allocated_item_data));
        }
        output["small_items"] = small_items_data;
        // appendix
        auto appendix = OrderedJson{};
        appendix["runnning_time"] = this->allocation_time();
        output["appendix"] = appendix;
        return output;
    }

    auto LargestFitFirstV2::add_item(const SmallItemWithSurface::Ptr small_item) -> void {
        this->quantity_manager.add_item(small_item);
        this->small_items.emplace(std::move(small_item));
        return;
    }

    auto LargestFitFirstV2::all_space() const {
        return iter::product(
            iter::range(this->space.size().z()), iter::range(this->space.size().y()), iter::range(this->space.size().x()));
    }

    auto LargestFitFirstV2::allocate() -> void {
        this->timer->start();
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

    auto LargestFitFirstV2::is_small_item_available(const SmallItemWithSurface::Ptr & small_item) const -> bool {
        return this->quantity_manager.quantity(small_item) != 0;
    }

    auto LargestFitFirstV2::is_item_within_large_object(const SmallItemWithSurface::Ptr & small_item, const Vector3D & position) const -> bool {
        return (small_item->measurement().x() + position.x() <= this->large_object.measurement().x())
            && (small_item->measurement().y() + position.y() <= this->large_object.measurement().y())
            && (small_item->measurement().z() + position.z() <= this->large_object.measurement().z());
    }

    auto LargestFitFirstV2::allocate_small_item(const SmallItemWithSurface::Ptr & small_item, const Vector3D & position) -> bool {
        const auto final_position = Vector3D{
            position.x() + small_item->measurement().x(),
            position.y() + small_item->measurement().y(),
            position.z() + small_item->measurement().z()};
        bool all_space_is_free = this->space.are_all_free(position, final_position);
        if (all_space_is_free) {
            this->allocated_small_items.emplace_back(small_item, position);
            this->quantity_manager.remove_one_item(small_item);
            this->space.occupy(position, final_position);
            return true;
        } else {
            return false;
        }
    }

    auto LargestFitFirstV2::allocated_items() const -> const decltype(this->allocated_small_items) & {
        return this->allocated_small_items;
    }

    auto LargestFitFirstV2::allocation_time() const -> double {
        try {
            return this->timer->getDurationSeconds();
        } catch (const std::runtime_error & error) {
            this->timer->stop();
            return this->timer->getDurationSeconds();
        }
    }

} // namespace algorithm

} // namespace packing
