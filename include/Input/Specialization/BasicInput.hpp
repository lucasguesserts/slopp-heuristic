#ifndef BASIC_INPUT_HPP_
#define BASIC_INPUT_HPP_

#include <string>

#include <nlohmann/json.hpp>

#include "Input/Input.hpp"
#include "LargeObject/Specialization/BasicLargeObject.hpp"
#include "Type/Quantity.hpp"

namespace packing {

template <typename ItemType>
class BasicInput : public Input<ItemType, BasicLargeObject> {
public:
    BasicInput(const std::string file_path)
        : BasicInput(Input<ItemType, BasicLargeObject>::load_json(file_path)) {}
    BasicInput(const nlohmann::json data)
        : Input<ItemType, BasicLargeObject>(data) {}

    virtual auto version() const -> InputVersion override {
        const auto version = this->data.at("version").template get<std::string>();
        if (version == "0.3.0") {
            return InputVersion::V_0_3_0;
        } else {
            throw std::runtime_error{"Invalid input version: " + version};
        }
    }

protected:
    virtual auto read_small_item(const nlohmann::json & small_item_data) const -> std::shared_ptr<ItemType> override {
        const auto small_item_measurements = Vector3D{
            small_item_data.at("measurement").at("x").get<CoordinateType>(),
            small_item_data.at("measurement").at("y").get<CoordinateType>(),
            small_item_data.at("measurement").at("z").get<CoordinateType>()};
        const auto small_item_quantity = small_item_data.at("quantity").get<Quantity>();
        return std::make_shared<ItemType>(small_item_measurements, small_item_quantity);
    }

    virtual auto read_large_object(const nlohmann::json & large_object_data) const -> std::shared_ptr<BasicLargeObject> override {
        return std::make_shared<BasicLargeObject>(Vector3D{
            large_object_data.at("measurement").at("x").get<CoordinateType>(),
            large_object_data.at("measurement").at("y").get<CoordinateType>(),
            large_object_data.at("measurement").at("z").get<CoordinateType>()});
    }
};

} // namespace packing

#endif
