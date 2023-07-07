#ifndef BASIC_INPUT_HPP_
#define BASIC_INPUT_HPP_

#include <nlohmann/json.hpp>

#include "Input/Input.hpp"
#include "SmallItem/Specialization/BasicSmallItem.hpp"
#include "LargeObject/BasicLargeObject.hpp"

namespace packing {

class BasicInput : public Input<BasicSmallItem::Ptr, BasicLargeObject> {
public:
    BasicInput(const std::string file_path);


    virtual auto version() const -> InputVersion override;

    auto large_object() const -> BasicLargeObject final override;
    auto small_items() const -> std::vector<BasicSmallItem::Ptr> final override;

private:
    std::vector<BasicSmallItem::Ptr> _small_items;
    BasicLargeObject _large_object;

    virtual auto read_small_item(const nlohmann::json & small_item_data) const -> BasicSmallItem::Ptr;
    virtual auto read_large_object(const nlohmann::json & large_object_data) const -> BasicLargeObject;
};

} // namespace packing

#endif
