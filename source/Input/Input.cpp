#include "Input/Input.hpp"

#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>

#include "SmallItem.hpp"

namespace packing {

Input::Input(const nlohmann::json & data)
    : data(data) {}

auto Input::type() const -> InputType {
    const auto type = this->data.at("type").get<std::string>();
    if (type == "input") {
        return InputType::INPUT;
    } else if (type == "output") {
        return InputType::OUTPUT;
    } else {
        throw std::runtime_error{"Invalid input type: " + type};
    }
}

auto Input::version() const -> InputVersion {
    const auto version = data.at("version").get<std::string>();
    if (version == "0.3.0") {
        return InputVersion::V_0_3_0;
    } else {
        throw std::runtime_error{"Invalid input version: " + version};
    }
}

auto Input::read_small_item(const nlohmann::json & small_item_data) -> SmallItem {
    const auto small_item_measurement_data = small_item_data.at("measurement");
    const auto small_item_measurements = Vector3D{
        small_item_measurement_data.at("x"),
        small_item_measurement_data.at("y"),
        small_item_measurement_data.at("z")};
    const auto small_item = SmallItem{small_item_measurements};
    return small_item;
}

auto Input::read_small_item_quantity(const nlohmann::json & small_item_data) -> Quantity {
    return small_item_data.at("quantity").get<Quantity>();
}

} // namespace packing
