#ifndef INPUT_HPP_
#define INPUT_HPP_

#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "Type/Quantity.hpp"
#include "LargeObject/BasicLargeObject.hpp"
#include "SmallItem.hpp"

namespace packing {

enum class InputType {
    INPUT,
    OUTPUT
};

enum class InputVersion {
    V_0_3_0
};

class Input {
public:
    Input(const nlohmann::json & data);
    ~Input() = default;

    auto type() const -> InputType;
    auto version() const -> InputVersion;
    virtual auto large_object() const -> BasicLargeObject = 0;
    virtual auto small_items() const -> std::vector<SmallItem> = 0;
    virtual auto small_items_quantity() const -> std::vector<Quantity> = 0;

protected:
    const nlohmann::json data;

    static auto read_small_item(const nlohmann::json & small_item_data) -> SmallItem;
    static auto read_small_item_quantity(const nlohmann::json & small_item_data) -> Quantity;
};

using InputPtr = std::unique_ptr<Input>;

} // namespace packing

#endif
