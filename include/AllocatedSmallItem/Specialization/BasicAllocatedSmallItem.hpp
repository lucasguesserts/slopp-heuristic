#ifndef BASIC_ALLOCATED_SMALL_ITEM_HPP_
#define BASIC_ALLOCATED_SMALL_ITEM_HPP_

#include <memory>
#include <utility>

#include "AllocatedSmallItem/AllocatedSmallItem.hpp"
#include "Geometry/Vector3D.hpp"

namespace packing {

template <typename ItemType>
class BasicAllocatedSmallItem : public AllocatedSmallItem<ItemType> {
public:
    BasicAllocatedSmallItem(const std::shared_ptr<ItemType> type, const Vector3D position)
        : _type{std::move(type)}
        , _position{std::move(position)}
        , _final_position{type->measurement() + position} {}

    inline auto type() const -> ItemType final override {
        return *(this->_type);
    }

    inline auto position() const -> Vector3D final override {
        return this->_position;
    }

    inline auto final_position() const -> Vector3D final override {
        return this->_final_position;
    }

private:
    std::shared_ptr<ItemType> _type;
    Vector3D _position;
    Vector3D _final_position;
};

} // namespace packing

#endif
