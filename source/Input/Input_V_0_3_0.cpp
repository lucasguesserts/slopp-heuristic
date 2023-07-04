#include "Input/Input_V_0_3_0.hpp"

#include <algorithm>
#include <iterator>
#include <vector>

#include "LargeObject/BasicLargeObject.hpp"
#include "SmallItem.hpp"
#include "Algorithm/LargestFitFirst/SmallItemQuantityManager.hpp"

namespace packing {

Input_V_0_3_0::Input_V_0_3_0(const nlohmann::json & data)
    : Input(data) {}

auto Input_V_0_3_0::large_object() const -> BasicLargeObject {
    const auto large_object_data = this->data.at("large_object");
    const auto large_object_measurements = Vector3D{
        large_object_data.at("measurement").at("x"),
        large_object_data.at("measurement").at("y"),
        large_object_data.at("measurement").at("z")};
    const auto large_object = BasicLargeObject{large_object_measurements};
    return large_object;
}

auto Input_V_0_3_0::small_items() const -> std::vector<SmallItem> {
    const auto small_item_array = this->data.at("small_items");
    std::vector<SmallItem> small_items;
    small_items.reserve(small_item_array.size());
    std::transform(
        small_item_array.begin(),
        small_item_array.end(),
        std::back_insert_iterator(small_items),
        Input::read_small_item);
    return small_items;
}

auto Input_V_0_3_0::small_items_quantity() const -> std::vector<Quantity> {
    const auto small_item_array = this->data.at("small_items");
    std::vector<Quantity> small_items_quantity;
    small_items_quantity.reserve(small_item_array.size());
    std::transform(
        small_item_array.begin(),
        small_item_array.end(),
        std::back_insert_iterator(small_items_quantity),
        Input::read_small_item_quantity);
    return small_items_quantity;
}

} // namespace packing
