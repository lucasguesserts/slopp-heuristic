#include "LargestFitFirstAlgorithm.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>

#include "SmallItem.hpp"
#include "SmallItemQuantityManager.hpp"
#include "Vector3D.hpp"
#include "nlohmann/json.hpp"
#include <cppitertools/itertools.hpp>

#include "BoolCuboid.hpp"
#include "LargeObject.hpp"

using nlohmann::json;
using std::string;
using OrderedJson = nlohmann::ordered_json;

namespace packing {

LargestFitFirstAlgorithm::LargestFitFirstAlgorithm(const LargeObject large_object)
    : large_object(large_object)
    , space(large_object.size()) {}

auto LargestFitFirstAlgorithm::from_json(const json data) -> LargestFitFirstAlgorithm {
    // large object
    const auto large_object = LargeObject{Vector3D{
        data["large_object"]["length"].get<CoordinateType>(),
        data["large_object"]["width"].get<CoordinateType>(),
        data["large_object"]["height"].get<CoordinateType>()}};
    // algorithm
    auto algorithm = LargestFitFirstAlgorithm{large_object};
    // small items
    const auto small_items_data = data["small_items"];
    for (const auto & small_item_data : data["small_items"]) {
        const auto small_item = SmallItem{Vector3D{
            small_item_data["length"].get<CoordinateType>(),
            small_item_data["width"].get<CoordinateType>(),
            small_item_data["height"].get<CoordinateType>()}};
        const auto quantity = small_item_data["quantity"].get<Quantity>();
        algorithm.add_item(small_item, quantity);
    }
    return algorithm;
}

auto LargestFitFirstAlgorithm::to_json(const LargestFitFirstAlgorithm & algorithm) -> json {
    auto output = OrderedJson{};
    // metadata
    output["type"] = "output";
    output["version"] = "0.1.0";
    // large object
    auto large_object_data = OrderedJson{};
    large_object_data["length"] = algorithm.large_object.size().x();
    large_object_data["width"] = algorithm.large_object.size().y();
    large_object_data["height"] = algorithm.large_object.size().z();
    output["large_object"] = large_object_data;
    // small items
    auto small_items_data = json::array();
    for (const auto & allocated_small_item : algorithm.allocated_small_items) {
        auto allocated_item_data = OrderedJson{};
        allocated_item_data["length"] = allocated_small_item.size().x();
        allocated_item_data["width"] = allocated_small_item.size().y();
        allocated_item_data["height"] = allocated_small_item.size().z();
        allocated_item_data["x"] = allocated_small_item.position().x();
        allocated_item_data["y"] = allocated_small_item.position().y();
        allocated_item_data["z"] = allocated_small_item.position().z();
        small_items_data.emplace_back(std::move(allocated_item_data));
    }
    output["small_items"] = small_items_data;
    return output;
}

auto LargestFitFirstAlgorithm::add_item(const SmallItem small_item, const Quantity quantity) -> void {
    this->quantity_manager[small_item] = quantity;
    this->small_items.push_back(small_item);
    return;
}

auto LargestFitFirstAlgorithm::all_space() {
    return iter::product(
        iter::range(this->space.size().z()), iter::range(this->space.size().y()), iter::range(this->space.size().x()));
}

auto LargestFitFirstAlgorithm::allocate() -> void {
    this->sort_items_descendig_volume();
    for (auto && [z, y, x] : this->all_space()) {
        if (this->space.is_free(x, y, z)) {
            for (const auto & small_item : this->small_items) {
                if (!this->is_item_within_large_object(small_item, {x, y, z})) continue;
                if (!this->is_small_item_available(small_item)) continue;
                const auto sucessfully_added = this->allocate_small_item(small_item, {x, y, z});
                if (sucessfully_added) break;
            }
        }
    }
    return;
}

auto LargestFitFirstAlgorithm::is_small_item_available(const SmallItem & small_item) -> bool {
    return this->quantity_manager[small_item] != 0;
}

auto LargestFitFirstAlgorithm::sort_items_descendig_volume() -> void {
    std::sort(this->small_items.begin(), this->small_items.end(), compareSmallItems);
    std::reverse(this->small_items.begin(), this->small_items.end());
    return;
}

auto LargestFitFirstAlgorithm::is_item_within_large_object(const SmallItem & small_item, const Vector3D & position)
    -> bool {
    return (small_item.size().x() + position.x() <= this->large_object.size().x())
        && (small_item.size().y() + position.y() <= this->large_object.size().y())
        && (small_item.size().z() + position.z() <= this->large_object.size().z());
}

auto LargestFitFirstAlgorithm::allocate_small_item(const SmallItem & small_item, const Vector3D & position) -> bool {
    const auto final_position = Vector3D{
        position.x() + small_item.size().x(),
        position.y() + small_item.size().y(),
        position.z() + small_item.size().z()};
    bool all_space_is_free = this->space.are_all_free(position, final_position);
    if (all_space_is_free) {
        this->allocated_small_items.emplace_back(small_item, position);
        this->quantity_manager[small_item] -= 1;
        this->space.occupy(position, final_position);
        return true;
    } else {
        return false;
    }
}

} // namespace packing
