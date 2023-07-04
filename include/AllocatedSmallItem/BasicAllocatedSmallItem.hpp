#ifndef BASIC_ALLOCATED_SMALL_ITEM_HPP_
#define BASIC_ALLOCATED_SMALL_ITEM_HPP_

#include <memory>
#include <utility>

#include "Geometry/Vector3D.hpp"
#include "AllocatedSmallItem/AllocatedSmallItem.hpp"

namespace packing {

template <typename ItemType>
class BasicAllocatedSmallItem: public AllocatedSmallItem<ItemType> {
public:
    BasicAllocatedSmallItem(const std::shared_ptr<ItemType> type, const Vector3D position)
        : _type{std::move(type)}
        , _position{std::move(position)} {}

    inline auto type() const -> ItemType final override {
        return *(this->_type);
    }

    inline auto position() const -> Vector3D final override {
        return this->_position;
    }

private:
    std::shared_ptr<ItemType> _type;
    Vector3D _position;
};

} // namespace packing

#endif
