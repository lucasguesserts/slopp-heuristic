#include "SmallItem/Specialization/BasicSmallItem.hpp"
#include "SmallItem/Specialization/SmallItemWithSurface.hpp"
#include "Test/Test.hpp"
#include <catch2/benchmark/catch_benchmark.hpp>

#include "Algorithm/LargestFitFirst.hpp"
#include "Algorithm/LargestFitFirstV2.hpp"
#include "Input/Specialization/BasicInput.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;
using packing::algorithm::LargestFitFirst;
using packing::algorithm::LargestFitFirstV2;

TEST_CASE("case 1", "[benchmark][Algorithm]") {
    // a reduced version of the instance 1 of the set 1 of Bischoff and Ratcliff

    const auto data_dir = std::filesystem::path("benchmark/data/compare_algorithms/");
    const auto file_path = data_dir / "case_1.json";
    std::ifstream file(file_path);
    const json data = json::parse(file);
    auto input_v1 = packing::BasicInput<packing::BasicSmallItem>{data};
    auto input_v2 = packing::BasicInput<packing::SmallItemWithSurface>{data};
    file.close();

    BENCHMARK("LargestFitFirst") {
        auto algorithm = LargestFitFirst(input_v1);
        algorithm.allocate();
        return algorithm.allocated_items();
    };

    BENCHMARK("LargestFitFirstV2") {
        auto algorithm = LargestFitFirstV2(input_v2);
        algorithm.allocate();
        return algorithm.allocated_items();
    };
}
