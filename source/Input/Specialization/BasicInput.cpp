#include "Input/Specialization/BasicInput.hpp"

#include <memory>

#include <nlohmann/json.hpp>

#include "LargeObject/Specialization/BasicLargeObject.hpp"
#include "SmallItem/Specialization/BasicSmallItem.hpp"
#include "Type/Quantity.hpp"

namespace packing {

BasicInput::BasicInput(const std::string file_path)
    : BasicInput(Input::load_json(file_path)) {}

BasicInput::BasicInput(const nlohmann::json data)
    : Input(data) {}

auto BasicInput::version() const -> InputVersion {
    const auto version = this->data.at("version").get<std::string>();
    if (version == "0.3.0") {
        return InputVersion::V_0_3_0;
    } else {
        throw std::runtime_error{"Invalid input version: " + version};
    }
}

auto BasicInput::read_small_item(const nlohmann::json & small_item_data) const -> BasicSmallItem::Ptr {
    const auto small_item_measurements = Vector3D{
        small_item_data.at("measurement").at("x").get<CoordinateType>(),
        small_item_data.at("measurement").at("y").get<CoordinateType>(),
        small_item_data.at("measurement").at("z").get<CoordinateType>()};
    const auto small_item_quantity = small_item_data.at("quantity").get<Quantity>();
    return std::make_shared<BasicSmallItem>(small_item_measurements, small_item_quantity);
}

auto BasicInput::read_large_object(const nlohmann::json & large_object_data) const -> std::shared_ptr<BasicLargeObject> {
    return std::make_shared<BasicLargeObject>(Vector3D{
        large_object_data.at("measurement").at("x").get<CoordinateType>(),
        large_object_data.at("measurement").at("y").get<CoordinateType>(),
        large_object_data.at("measurement").at("z").get<CoordinateType>()});
}

} // namespace packing
