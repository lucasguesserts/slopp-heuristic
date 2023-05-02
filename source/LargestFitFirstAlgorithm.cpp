#include "LargestFitFirstAlgorithm.hpp"

#include <algorithm>
#include <utility>

#include <cppitertools/itertools.hpp>

#include "BoolCuboid.hpp"
#include "LargeObject.hpp"

namespace packing {

LargestFitFirstAlgorithm::LargestFitFirstAlgorithm(const LargeObject large_object)
    : large_object(large_object)
    , space(large_object.size()) {}

auto LargestFitFirstAlgorithm::add_item(const SmallItem small_item, const Quantity quantity) -> void {
    this->quantity_manager[small_item] = quantity;
    this->small_items.push_back(small_item);
    return;
}

auto LargestFitFirstAlgorithm::all_space() {
    return iter::product(
        iter::range(this->space.size().z()), iter::range(this->space.size().y()), iter::range(this->space.size().x()));
}

auto LargestFitFirstAlgorithm::allocate() -> void {
    this->sort_items_descendig_volume();
    for (auto && [z, y, x] : this->all_space()) {
        if (this->space.is_free(x, y, z)) {
            for (const auto & small_item : this->small_items) {
                if (!this->is_item_within_large_object(small_item, {x, y, z})) continue;
                if (!this->is_small_item_available(small_item)) continue;
                const auto sucessfully_added = this->allocate_small_item(small_item, {x, y, z});
                if (sucessfully_added) break;
            }
        }
    }
    return;
}

auto LargestFitFirstAlgorithm::is_small_item_available(const SmallItem & small_item) -> bool {
    return this->quantity_manager[small_item] != 0;
}

auto LargestFitFirstAlgorithm::sort_items_descendig_volume() -> void {
    std::sort(this->small_items.begin(), this->small_items.end(), compareSmallItems);
    std::reverse(this->small_items.begin(), this->small_items.end());
    return;
}

auto LargestFitFirstAlgorithm::is_item_within_large_object(const SmallItem & small_item, const Vector3D & position)
    -> bool {
    return (small_item.size().x() + position.x() <= this->large_object.size().x())
        && (small_item.size().y() + position.y() <= this->large_object.size().y())
        && (small_item.size().z() + position.z() <= this->large_object.size().z());
}

auto LargestFitFirstAlgorithm::allocate_small_item(const SmallItem & small_item, const Vector3D & position) -> bool {
    const auto final_position = Vector3D{
        position.x() + small_item.size().x(),
        position.y() + small_item.size().y(),
        position.z() + small_item.size().z()};
    bool all_space_is_free = this->space.are_all_free(position, final_position);
    if (all_space_is_free) {
        this->allocated_small_items.emplace_back(small_item, position);
        this->quantity_manager[small_item] -= 1;
        this->space.occupy(position, final_position);
        return true;
    } else {
        return false;
    }
}

} // namespace packing
