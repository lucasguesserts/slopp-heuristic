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

TEST_CASE("Bischoff and Ratcliff - set 1 - instance 1", "[benchmark][Algorithm]") {

    const auto data_dir = std::filesystem::path("benchmark/data/compare_algorithms/");
    const auto file_path = data_dir / "1.json";
    std::ifstream file(file_path);
    const json data = json::parse(file);
    file.close();

    BENCHMARK("LargestFitFirstAlgorithm") {
        auto algorithm = LargestFitFirstAlgorithm(data);
        algorithm.allocate();
        return algorithm.allocated_items();
    };
}
