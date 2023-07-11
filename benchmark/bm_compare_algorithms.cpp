#include "SmallItem/Specialization/BasicSmallItem.hpp"
#include "SmallItem/Specialization/SmallItemWithSurface.hpp"
#include "Test/Test.hpp"
#include <catch2/benchmark/catch_benchmark.hpp>

#include "Algorithm/LargestFitFirst.hpp"
#include "Algorithm/LargestFitFirstV2.hpp"
#include "Algorithm/LargestFitFirstV3.hpp"
#include "AllocatedSmallItem/Specialization/BasicAllocatedSmallItem.hpp"
#include "Input/Specialization/BasicInput.hpp"
#include "SmallItem/Specialization/BasicSmallItem.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;
using packing::BasicAllocatedSmallItem;
using packing::BasicSmallItem;
using packing::algorithm::LargestFitFirst;
using packing::algorithm::LargestFitFirstV2;
using packing::algorithm::LargestFitFirstV3;

TEST_CASE("case 1", "[benchmark][Algorithm]") {
    // a reduced version of the instance 1 of the set 1 of Bischoff and Ratcliff

    const auto data_dir = std::filesystem::path("benchmark/data/compare_algorithms/");
    const auto file_path = data_dir / "case_1.json";
    std::ifstream file(file_path);
    const json data = json::parse(file);
    auto input_v1 = packing::BasicInput<packing::BasicSmallItem>{data};
    auto input_v2 = packing::BasicInput<packing::SmallItemWithSurface>{data};
    auto input_v3 = packing::BasicInput<packing::BasicSmallItem>{data};
    file.close();

    BENCHMARK("LargestFitFirst") {
        auto algorithm = LargestFitFirst<BasicSmallItem, BasicSmallItem::Hash, BasicAllocatedSmallItem<BasicSmallItem>>(input_v1);
        algorithm.allocate();
        return algorithm.allocated_items();
    };

    BENCHMARK("LargestFitFirstV2") {
        auto algorithm = LargestFitFirstV2(input_v2);
        algorithm.allocate();
        return algorithm.allocated_items();
    };

    BENCHMARK("LargestFitFirstV3") {
        auto algorithm = LargestFitFirstV3(input_v3);
        algorithm.allocate();
        return algorithm.allocated_items();
    };
}
