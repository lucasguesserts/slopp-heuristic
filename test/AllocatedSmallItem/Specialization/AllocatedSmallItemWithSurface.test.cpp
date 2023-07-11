#include "Test/Test.hpp"

#include "AllocatedSmallItem/Specialization/AllocatedSmallItemWithSurface.hpp"
#include "Geometry/Surface.hpp"
#include "Geometry/Vector3D.hpp"
#include "SmallItem/Specialization/SmallItemWithSurface.hpp"

using namespace packing;

TEST_CASE("constructor", "[AllocatedSmallItem]") {
    const auto measurement = Vector3D{1, 2, 3};
    const auto quantity = Quantity{4};
    const auto position = Vector3D{5, 6, 7};
    const auto final_position = Vector3D{6, 8, 10};
    const auto small_item = std::make_shared<SmallItemWithSurface>(measurement, quantity);
    const auto allocated_small_item = AllocatedSmallItemWithSurface{small_item, position};
    // check
    CHECK(allocated_small_item.type().measurement() == measurement);
    CHECK(allocated_small_item.type().quantity() == quantity);
    CHECK(allocated_small_item.position() == position);
    CHECK(allocated_small_item.final_position() == final_position);
}

TEST_CASE("surface", "[AllocatedSmallItem]") {
    // measurement
    const auto measurement_x = CoordinateType{2};
    const auto measurement_y = CoordinateType{3};
    const auto measurement_z = CoordinateType{5};
    const auto measurement = Vector3D{measurement_x, measurement_y, measurement_z};
    // quantity
    const auto quantity = Quantity{1};
    // position
    const auto position_x = CoordinateType{7};
    const auto position_y = CoordinateType{11};
    const auto position_z = CoordinateType{13};
    const auto position = Vector3D{position_x, position_y, position_z};
    // item
    const auto small_item = std::make_shared<SmallItemWithSurface>(measurement, quantity);
    const auto allocated_small_item = AllocatedSmallItemWithSurface{small_item, position};
    // expected surface
    const auto expected = Surface{
        {7, 11, 12},
        {7, 12, 12},
        {7, 13, 12},
        {8, 11, 12},
        {8, 12, 12},
        {8, 13, 12},
        {7, 11, 18},
        {7, 12, 18},
        {7, 13, 18},
        {8, 11, 18},
        {8, 12, 18},
        {8, 13, 18},
        {7, 10, 13},
        {7, 10, 14},
        {7, 10, 15},
        {7, 10, 16},
        {7, 10, 17},
        {8, 10, 13},
        {8, 10, 14},
        {8, 10, 15},
        {8, 10, 16},
        {8, 10, 17},
        {7, 14, 13},
        {7, 14, 14},
        {7, 14, 15},
        {7, 14, 16},
        {7, 14, 17},
        {8, 14, 13},
        {8, 14, 14},
        {8, 14, 15},
        {8, 14, 16},
        {8, 14, 17},
        {6, 11, 13},
        {6, 11, 14},
        {6, 11, 15},
        {6, 11, 16},
        {6, 11, 17},
        {6, 12, 13},
        {6, 12, 14},
        {6, 12, 15},
        {6, 12, 16},
        {6, 12, 17},
        {6, 13, 13},
        {6, 13, 14},
        {6, 13, 15},
        {6, 13, 16},
        {6, 13, 17},
        {9, 11, 13},
        {9, 11, 14},
        {9, 11, 15},
        {9, 11, 16},
        {9, 11, 17},
        {9, 12, 13},
        {9, 12, 14},
        {9, 12, 15},
        {9, 12, 16},
        {9, 12, 17},
        {9, 13, 13},
        {9, 13, 14},
        {9, 13, 15},
        {9, 13, 16},
        {9, 13, 17}};
    // check
    CHECK(allocated_small_item.surface() == expected);
}
