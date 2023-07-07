#include "LargeObject/BasicLargeObject.hpp"
#include "SmallItem/Specialization/BasicSmallItem.hpp"
#include "Test/Test.hpp"

#include <filesystem>
#include <vector>

#include "itertools.hpp"

#include "Input/Specialization/BasicInput.hpp"

#include "SmallItem/Specialization/BasicSmallItem.hpp"

using namespace packing;

const auto data_dir = std::filesystem::path("test/data/Input/");

TEST_CASE("all cases", "[LargestFitFirst]") {
    const auto file_path = data_dir / "01.json";
    const auto input = BasicInput(file_path);
    SECTION("basic properties") {
        CHECK(input.version() == InputVersion::V_0_3_0);
    }
    SECTION("large object") {
        const auto large_object = input.large_object();
        const auto expected = BasicLargeObject{{11, 13, 17}};
        CHECK(large_object == expected);
    }
    SECTION("small items") {
        const auto small_items = input.small_items();
        const auto expected = std::vector<BasicSmallItem::Ptr>{
            std::make_shared<BasicSmallItem>(Vector3D{3, 5, 7}, 100),
            std::make_shared<BasicSmallItem>(Vector3D{6, 10, 14}, 200),
        };
        for (auto && [small_item, expected_small_item] : iter::zip(small_items, expected)) {
            CHECK(*small_item == *expected_small_item);
        }
    }
}
