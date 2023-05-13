#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

#include "LargestFitFirstAlgorithm.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;
using packing::LargestFitFirstAlgorithm;

TEST_CASE("case 1", "[benchmark][Algorithm]") {
    // a reduced version of the instance 1 of the set 1 of Bischoff and Ratcliff

    const auto data_dir = std::filesystem::path("benchmark/data/compare_algorithms/");
    const auto file_path = data_dir / "case_1.json";
    std::ifstream file(file_path);
    const json data = json::parse(file);
    file.close();

    BENCHMARK("LargestFitFirstAlgorithm") {
        auto algorithm = LargestFitFirstAlgorithm(data);
        algorithm.allocate();
        return algorithm.allocated_items();
    };
}
