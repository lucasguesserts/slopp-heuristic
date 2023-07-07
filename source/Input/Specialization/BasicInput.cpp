#include "Input/Specialization/BasicInput.hpp"

#include <memory>

#include <nlohmann/json.hpp>

#include "LargeObject/Specialization/BasicLargeObject.hpp"
#include "SmallItem/Specialization/BasicSmallItem.hpp"
#include "Type/Quantity.hpp"

namespace packing {

BasicInput::BasicInput(const std::string file_path)
    : Input(file_path)
    , _large_object(this->read_large_object(data.at("large_object"))) {
    if (this->version() != InputVersion::V_0_3_0) {
        throw std::runtime_error{"input version not supported: " + data.at("version").get<std::string>()};
    }
    for (const auto & small_item_data : data.at("small_items")) {
        _small_items.push_back(this->read_small_item(small_item_data));
    }
    return;
}

auto BasicInput::version() const -> InputVersion {
    const auto version = this->data.at("version").get<std::string>();
    if (version == "0.3.0") {
        return InputVersion::V_0_3_0;
    } else {
        throw std::runtime_error{"Invalid input version: " + version};
    }
}

auto BasicInput::large_object() const -> BasicLargeObject {
    return this->_large_object;
}

auto BasicInput::small_items() const -> std::vector<BasicSmallItem::Ptr> {
    return this->_small_items;
}

auto BasicInput::read_small_item(const nlohmann::json & small_item_data) const -> BasicSmallItem::Ptr {
    const auto small_item_measurements = Vector3D{
        small_item_data.at("measurement").at("x").get<CoordinateType>(),
        small_item_data.at("measurement").at("y").get<CoordinateType>(),
        small_item_data.at("measurement").at("z").get<CoordinateType>()};
    const auto small_item_quantity = small_item_data.at("quantity").get<Quantity>();
    return std::make_shared<BasicSmallItem>(small_item_measurements, small_item_quantity);
}

auto BasicInput::read_large_object(const nlohmann::json & large_object_data) const -> BasicLargeObject {
    return BasicLargeObject{Vector3D{
        large_object_data.at("measurement").at("x").get<CoordinateType>(),
        large_object_data.at("measurement").at("y").get<CoordinateType>(),
        large_object_data.at("measurement").at("z").get<CoordinateType>()}};
}

} // namespace packing
