#ifndef MAXIMAL_EMPTY_SPACE_EMPTY_SPACE_OPERATOR_HPP_
#define MAXIMAL_EMPTY_SPACE_EMPTY_SPACE_OPERATOR_HPP_

#include <vector>

#include "AllocatedSmallItem/AllocatedSmallItem.hpp"
#include "EmptySpace/MaximalEmptySpace/EmptySpace.hpp"
#include "EmptySpace/MaximalEmptySpace/Specialization/BasicEmptySpace.hpp"

namespace packing {

namespace maximal_empty_space {

    template <typename ItemType>
    class EmptySpaceOperator {
    public:
        EmptySpaceOperator() = default;
        ~EmptySpaceOperator() = default;

        auto has_overlap(
            const BasicEmptySpace & empty_space,
            const AllocatedSmallItem<ItemType> & allocated_small_item)
            const -> bool {
            return ((empty_space.position().x() < allocated_small_item.final_position().x()) && (empty_space.final_position().x() > allocated_small_item.position().x()) && (empty_space.position().y() < allocated_small_item.final_position().y()) && (empty_space.final_position().y() > allocated_small_item.position().y()) && (empty_space.position().z() < allocated_small_item.final_position().z()) && (empty_space.final_position().z() > allocated_small_item.position().z()));
        }

        auto remaining_empty_space(
            const BasicEmptySpace & empty_space,
            const AllocatedSmallItem<ItemType> & allocated_small_item)
            const -> std::vector<BasicEmptySpace> {
            if (!this->has_overlap(empty_space, allocated_small_item)) {
                return {empty_space};
            }
            /* TODO: the 'if' above is not really necessary if one
             * implements a collection of empty spaces that can
             * handle Empty Spaces which are inside one another.
             * In the case of the 'if' above, three Empty Spaces
             * would be created, and they would all be equal to
             * the original Empty Space, so that the final result
             * would be a collection with only one Empty Space.
             */
            auto result = std::vector<BasicEmptySpace>{};
            // x
            //// back
            if (allocated_small_item.position().x() > empty_space.position().x()) {
                result.push_back(this->cut_space_back(empty_space, allocated_small_item));
            }
            //// front
            if (allocated_small_item.final_position().x() < empty_space.final_position().x()) {
                result.push_back(this->cut_space_front(empty_space, allocated_small_item));
            }
            // y
            // right
            if (allocated_small_item.position().y() > empty_space.position().y()) {
                result.push_back(this->cut_space_right(empty_space, allocated_small_item));
            }
            //// left
            if (allocated_small_item.final_position().y() < empty_space.final_position().y()) {
                result.push_back(this->cut_space_left(empty_space, allocated_small_item));
            }
            // z
            //// bottom
            if (allocated_small_item.position().z() > empty_space.position().z()) {
                result.push_back(this->cut_space_bottom(empty_space, allocated_small_item));
            }
            //// top
            if (allocated_small_item.final_position().z() < empty_space.final_position().z()) {
                result.push_back(this->cut_space_top(empty_space, allocated_small_item));
            }
            return result;
        }

        auto add_to_collection(
            const BasicEmptySpace & empty_space,
            std::vector<BasicEmptySpace> & empty_space_collection)
            const -> void {
            // case 'empty_space' is inside one of the empty spaces in 'empty_space_collection'
            for (const auto & other_empty_space : empty_space_collection) {
                if (empty_space.is_inside(other_empty_space)) {
                    return;
                }
            }
            // case 'empty_space' is NOT inside one of the empty spaces in 'empty_space_collection'
            // and 'empty_space' contains zero or more one of the empty spaces in 'empty_space_collection'
            for (auto it = empty_space_collection.begin(); it != empty_space_collection.end();) {
                if (it->is_inside(empty_space)) {
                    it = empty_space_collection.erase(it);
                } else {
                    ++it;
                }
            }
            empty_space_collection.push_back(empty_space);
            return;
        }

        auto extend_collection(
            std::vector<BasicEmptySpace> & to_extend,
            const std::vector<BasicEmptySpace> & extension)
            const -> void {
            for (const auto & empty_space : extension) {
                this->add_to_collection(empty_space, to_extend);
            }
            return;
        }

        auto cut_collection(
            const std::vector<BasicEmptySpace> & empty_space_collection,
            const AllocatedSmallItem<ItemType> & allocated_small_item)
            const -> std::vector<BasicEmptySpace> {
            auto result = std::vector<BasicEmptySpace>{};
            for (const auto & empty_space : empty_space_collection) {
                const auto remaining_empty_spaces = this->remaining_empty_space(empty_space, allocated_small_item);
                this->extend_collection(result, remaining_empty_spaces);
            }
            return result;
        }

    private:
        auto cut_space_back(
            const BasicEmptySpace & empty_space,
            const AllocatedSmallItem<ItemType> & allocated_small_item)
            const -> BasicEmptySpace {
            const auto position = Vector3D{
                empty_space.position().x(),
                empty_space.position().y(),
                empty_space.position().z()};
            const auto measurement = Vector3D{
                allocated_small_item.position().x() - empty_space.position().x(),
                empty_space.measurement().y(),
                empty_space.measurement().z()};
            return BasicEmptySpace(position, measurement);
        }

        auto cut_space_front(
            const BasicEmptySpace & empty_space,
            const AllocatedSmallItem<ItemType> & allocated_small_item)
            const -> BasicEmptySpace {
            const auto position = Vector3D{
                allocated_small_item.final_position().x(),
                empty_space.position().y(),
                empty_space.position().z()};
            const auto measurement = Vector3D{
                empty_space.final_position().x() - allocated_small_item.final_position().x(),
                empty_space.measurement().y(),
                empty_space.measurement().z()};
            return BasicEmptySpace(position, measurement);
        }

        auto cut_space_right(
            const BasicEmptySpace & empty_space,
            const AllocatedSmallItem<ItemType> & allocated_small_item)
            const -> BasicEmptySpace {
            const auto position = Vector3D{
                empty_space.position().x(),
                empty_space.position().y(),
                empty_space.position().z()};
            const auto measurement = Vector3D{
                empty_space.measurement().x(),
                allocated_small_item.position().y() - empty_space.position().y(),
                empty_space.measurement().z()};
            return BasicEmptySpace(position, measurement);
        }

        auto cut_space_left(
            const BasicEmptySpace & empty_space,
            const AllocatedSmallItem<ItemType> & allocated_small_item)
            const -> BasicEmptySpace {
            const auto position = Vector3D{
                empty_space.position().x(),
                allocated_small_item.final_position().y(),
                empty_space.position().z()};
            const auto measurement = Vector3D{
                empty_space.measurement().x(),
                empty_space.final_position().y() - allocated_small_item.final_position().y(),
                empty_space.measurement().z()};
            return BasicEmptySpace(position, measurement);
        }

        auto cut_space_bottom(
            const BasicEmptySpace & empty_space,
            const AllocatedSmallItem<ItemType> & allocated_small_item)
            const -> BasicEmptySpace {
            const auto position = Vector3D{
                empty_space.position().x(),
                empty_space.position().y(),
                empty_space.position().z()};
            const auto measurement = Vector3D{
                empty_space.measurement().x(),
                empty_space.measurement().y(),
                allocated_small_item.position().z() - empty_space.position().z()};
            return BasicEmptySpace(position, measurement);
        }

        auto cut_space_top(
            const BasicEmptySpace & empty_space,
            const AllocatedSmallItem<ItemType> & allocated_small_item)
            const -> BasicEmptySpace {
            const auto position = Vector3D{
                empty_space.position().x(),
                empty_space.position().y(),
                allocated_small_item.final_position().z()};
            const auto measurement = Vector3D{
                empty_space.measurement().x(),
                empty_space.measurement().y(),
                empty_space.final_position().z() - allocated_small_item.final_position().z()};
            return BasicEmptySpace(position, measurement);
        }
    };

} // namespace maximal_empty_space

} // namespace packing

#endif
