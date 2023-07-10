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

        auto cut_empty_space(
            const BasicEmptySpace & empty_space,
            const AllocatedSmallItem<ItemType> & allocated_small_item)
            const -> std::vector<BasicEmptySpace> {
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