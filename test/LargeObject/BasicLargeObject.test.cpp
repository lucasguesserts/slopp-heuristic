#include "Test.hpp"

#include "LargeObject/BasicLargeObject.hpp"
#include "Geometry/Vector3D.hpp"

using namespace packing;

TEST_CASE("constructor", "[LargeObject]") {
    const auto measurement = Vector3D{1, 2, 3};
    const auto large_object = BasicLargeObject{measurement};
    CHECK(large_object.measurement() == measurement);
}
