#ifndef BASIC_INPUT_HPP_
#define BASIC_INPUT_HPP_

#include <nlohmann/json.hpp>

#include "Input/Input.hpp"
#include "LargeObject/Specialization/BasicLargeObject.hpp"
#include "SmallItem/Specialization/BasicSmallItem.hpp"

namespace packing {

class BasicInput : public Input<BasicSmallItem, BasicLargeObject> {
public:
    BasicInput(const std::string file_path);
    BasicInput(const nlohmann::json data);

    virtual auto version() const -> InputVersion override;

protected:
    virtual auto read_small_item(const nlohmann::json & small_item_data) const -> BasicSmallItem::Ptr override;
    virtual auto read_large_object(const nlohmann::json & large_object_data) const -> std::shared_ptr<BasicLargeObject> override;
};

} // namespace packing

#endif
