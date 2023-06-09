#ifndef LARGEST_FIT_FIRST_ALGORITHM_HPP_
#define LARGEST_FIT_FIRST_ALGORITHM_HPP_

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <itertools.hpp>
#include <nlohmann/json.hpp>

#include "Algorithm/LargestFitFirst/BoolCuboid.hpp"
#include "Geometry/Vector3D.hpp"
#include "Input/Specialization/BasicInput.hpp"
#include "LargeObject/Specialization/BasicLargeObject.hpp"
#include "SmallItem/Container/OrderedSmallItemsByVolume.hpp"
#include "SmallItem/Container/QuantityManager.hpp"
#include "Timer/Timer.hpp"
#include "Timer/UserTimer.hpp"

namespace packing {
namespace algorithm {

    template <typename ItemType, typename ItemTypeHash, typename AllocatedItemType>
    class LargestFitFirst {
    public:
        LargestFitFirst(BasicInput<ItemType> & data)
            : LargestFitFirst{data.large_object()} {
            for (const auto & small_item : data.small_items()) {
                this->add_item(small_item);
            }
            return;
        }

        auto add_item(const std::shared_ptr<ItemType> small_item) -> void {
            this->quantity_manager.add_item(small_item);
            this->small_items.insert(std::move(small_item));
            return;
        }

        virtual auto allocate() -> void {
            this->timer->start();
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
            this->timer->stop();
            return;
        }

        auto allocated_items() const -> const std::vector<AllocatedItemType> & {
            return this->allocated_small_items;
        }

        auto allocation_time() const -> double {
            try {
                return this->timer->getDurationSeconds();
            } catch (const std::runtime_error & error) {
                this->timer->stop();
                return this->timer->getDurationSeconds();
            }
        }

        auto to_json() const -> nlohmann::json {
            auto output = nlohmann::ordered_json{};
            // metadata
            output["type"] = "output";
            output["version"] = "0.2.0";
            // large object
            auto large_object_data = nlohmann::ordered_json{};
            large_object_data["length"] = this->large_object.measurement().x();
            large_object_data["width"] = this->large_object.measurement().y();
            large_object_data["height"] = this->large_object.measurement().z();
            output["large_object"] = large_object_data;
            // small items
            auto small_items_data = nlohmann::json::array();
            for (const auto & allocated_small_item : this->allocated_small_items) {
                auto allocated_item_data = nlohmann::ordered_json{};
                allocated_item_data["length"] = allocated_small_item.type().measurement().x();
                allocated_item_data["width"] = allocated_small_item.type().measurement().y();
                allocated_item_data["height"] = allocated_small_item.type().measurement().z();
                allocated_item_data["x"] = allocated_small_item.position().x();
                allocated_item_data["y"] = allocated_small_item.position().y();
                allocated_item_data["z"] = allocated_small_item.position().z();
                small_items_data.emplace_back(std::move(allocated_item_data));
            }
            output["small_items"] = small_items_data;
            // appendix
            auto appendix = nlohmann::ordered_json{};
            appendix["runnning_time"] = this->allocation_time();
            output["appendix"] = appendix;
            return output;
        }

    protected:
        const BasicLargeObject large_object;
        BoolCuboid space;
        OrderedSmallItemsByVolume<std::shared_ptr<ItemType>> small_items;
        QuantityManager<std::shared_ptr<ItemType>, ItemTypeHash> quantity_manager;
        std::vector<AllocatedItemType> allocated_small_items;
        TimerPtr timer;

        LargestFitFirst(const BasicLargeObject large_object)
            : large_object(large_object)
            , space(large_object.measurement())
            , timer(UserTimer::make()) {}

        auto all_space() const {
            return iter::product(
                iter::range(this->space.size().z()), iter::range(this->space.size().y()), iter::range(this->space.size().x()));
        }

        auto is_small_item_available(const std::shared_ptr<ItemType> & small_item) const -> bool {
            return this->quantity_manager.quantity(small_item) != 0;
        }

        auto is_item_within_large_object(const std::shared_ptr<ItemType> & small_item, const Vector3D & position) const -> bool {
            return (small_item->measurement().x() + position.x() <= this->large_object.measurement().x())
                && (small_item->measurement().y() + position.y() <= this->large_object.measurement().y())
                && (small_item->measurement().z() + position.z() <= this->large_object.measurement().z());
        }

        auto allocate_small_item(const std::shared_ptr<ItemType> & small_item, const Vector3D & position) -> bool {
            const auto final_position = Vector3D{
                position.x() + small_item->measurement().x(),
                position.y() + small_item->measurement().y(),
                position.z() + small_item->measurement().z()};
            bool all_space_is_free = this->space.are_all_free(position, final_position);
            if (all_space_is_free) {
                this->allocated_small_items.emplace_back(small_item, position);
                this->quantity_manager.remove_one_item(small_item);
                this->space.occupy(position, final_position);
                return true;
            } else {
                return false;
            }
        }
    };

} // namespace algorithm

} // namespace packing

#endif
