#ifndef SMALL_ITEMS_QUANTITY_MANAGER_HPP_
#define SMALL_ITEMS_QUANTITY_MANAGER_HPP_

#include <cstddef>
#include <stdexcept>
#include <unordered_map>

#include <boost/functional/hash.hpp>

#include "Type/Quantity.hpp"

namespace packing {

template <typename ItemTypePtr, typename ItemTypeHash>
class QuantityManager : private std::unordered_map<ItemTypePtr, Quantity, ItemTypeHash> {
public:
    auto add_item(const ItemTypePtr & small_item) -> void {
        if (small_item->quantity() == 0) {
            throw std::runtime_error("SmallItemQuantityManager::add_item: small item quantity is zero");
        }
        if (this->find(small_item) == this->end()) {
            (*this)[small_item] = small_item->quantity();
        } else {
            (*this)[small_item] += small_item->quantity();
        }
        return;
    }

    auto remove_one_item(const ItemTypePtr & small_item) -> void {
        if (this->find(small_item) == this->end()) {
            throw std::runtime_error("SmallItemQuantityManager::remove_one_item: small item not found");
        }
        (*this)[small_item] -= 1;
        if ((*this)[small_item] == 0) {
            this->erase(small_item);
        }
        return;
    }

    auto quantity(const ItemTypePtr & small_item) -> Quantity {
        if (this->find(small_item) == this->end()) {
            return 0;
        }
        return (*this)[small_item];
    }
};

} // namespace packing

#endif
