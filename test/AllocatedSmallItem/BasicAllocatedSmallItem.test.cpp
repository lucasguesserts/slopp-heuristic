#include "Test/Test.hpp"

#include "AllocatedSmallItem/Specialization/BasicAllocatedSmallItem.hpp"

#include "Geometry/Vector3D.hpp"
#include "SmallItem/Specialization/BasicSmallItem.hpp"

using namespace packing;

TEST_CASE("constructor", "[BasicSmallItem]") {
    const auto measurement = Vector3D{1, 2, 3};
    const auto quantity = Quantity{4};
    const auto item_type_ptr = std::make_shared<BasicSmallItem>(measurement, quantity);
    const auto position = Vector3D{4, 5, 6};
    const auto final_position = Vector3D{5, 7, 9};
    const auto allocated_item = BasicAllocatedSmallItem<BasicSmallItem>{item_type_ptr, position};
    CHECK(allocated_item.type() == *item_type_ptr);
    CHECK(allocated_item.position() == position);
    CHECK(allocated_item.final_position() == final_position);
}
