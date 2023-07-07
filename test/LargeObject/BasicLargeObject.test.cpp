#include "Test/Test.hpp"

#include "Geometry/Vector3D.hpp"
#include "LargeObject/Specialization/BasicLargeObject.hpp"

using namespace packing;

TEST_CASE("constructor", "[LargeObject]") {
    const auto measurement = Vector3D{1, 2, 3};
    const auto large_object = BasicLargeObject{measurement};
    CHECK(large_object.measurement() == measurement);
}

TEST_CASE("equality", "[LargeObject]") {
    const auto measurement = Vector3D{1, 2, 3};
    const auto lhs = BasicLargeObject{measurement};
    const auto rhs = BasicLargeObject{measurement};
    CHECK(lhs == rhs);
}
