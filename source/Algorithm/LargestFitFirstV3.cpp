#include "Algorithm/LargestFitFirstV3.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>

#include "SmallItem/Specialization/BasicSmallItem.hpp"
#include "nlohmann/json.hpp"
#include <itertools.hpp>

#include "Algorithm/LargestFitFirst/BoolCuboid.hpp"
#include "AllocatedSmallItem/Specialization/BasicAllocatedSmallItem.hpp"
#include "Geometry/Vector3D.hpp"
#include "LargeObject/Specialization/BasicLargeObject.hpp"
#include "SmallItem/Specialization/SmallItemWithSurface.hpp"
#include "Timer/Timer.hpp"
#include "Timer/UserTimer.hpp"

using packing::maximal_empty_space::BasicEmptySpace;

using nlohmann::json;
using std::string;
using OrderedJson = nlohmann::ordered_json;

namespace packing {

namespace algorithm {

    LargestFitFirstV3::LargestFitFirstV3(const BasicLargeObject large_object)
        : LargestFitFirst{large_object} {}

    LargestFitFirstV3::LargestFitFirstV3(BasicInput<BasicSmallItem> & data, const std::vector<double> & sort_order)
        : LargestFitFirstV3{data.large_object()} {
        // small items
        for (const auto & small_item : data.small_items()) {
            this->add_item(small_item);
        }
        for (auto i = 0u; i < this->small_items.size(); ++i) {
            this->values_for_small_items_allocation_order[this->small_items[i]] = sort_order[i];
        }
        this->compare_small_items = [this](const std::shared_ptr<BasicSmallItem> & lhs, const std::shared_ptr<BasicSmallItem> & rhs) {
            return this->values_for_small_items_allocation_order[lhs] > this->values_for_small_items_allocation_order[rhs];
        };
        return;
    }

    auto LargestFitFirstV3::allocate() -> void {
        this->timer->start();
        std::sort(this->small_items.begin(), this->small_items.end(), this->compare_small_items);
        this->empty_space_operator.add_to_collection(
            BasicEmptySpace{{0, 0, 0}, this->large_object.measurement()},
            this->empty_spaces);
        while (!this->empty_spaces.empty()) {
            const auto empty_space = this->empty_spaces.back();
            bool item_allocated_in_this_space = false;
            for (const auto & small_item : this->small_items) {
                if (!this->item_fit_in_space(*small_item, empty_space)) continue;
                if (!this->is_small_item_available(small_item)) continue;
                this->place_item(small_item, empty_space);
                item_allocated_in_this_space = true;
                break;
            }
            if (!item_allocated_in_this_space) {
                this->empty_spaces.pop_back();
            }
        }
        this->timer->stop();
        return;
    }

    auto LargestFitFirstV3::item_fit_in_space(
        const BasicSmallItem & small_item,
        const BasicEmptySpace & empty_space)
        const -> bool {
        return small_item.measurement() <= empty_space.measurement();
    }

    // TODO: implement
    auto LargestFitFirstV3::place_item(
        const BasicSmallItem::Ptr small_item,
        const BasicEmptySpace & empty_space) -> void {
        this->allocated_small_items.emplace_back(small_item, empty_space.position());
        this->quantity_manager.remove_one_item(small_item);
        this->empty_spaces = this->empty_space_operator.cut_collection(this->empty_spaces, allocated_small_items.back());
        return;
    }

} // namespace algorithm

} // namespace packing
