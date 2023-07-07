#include "Test/Test.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <itertools.hpp>
#include <nlohmann/json.hpp>

#include "Input/Specialization/BasicInput.hpp"
#include "Algorithm/LargestFitFirst.hpp"

using json = nlohmann::json;

using namespace packing;
using namespace packing::algorithm;

const auto data_dir = std::filesystem::path("test/data/LargestFitFirst/");

TEST_CASE("all cases", "[LargestFitFirst]") {
    // data
    const auto cases = std::vector<std::string>{"01", "02", "03", "04"};
    for (const auto & case_name : cases) {
        SECTION("case " + case_name) {
            const auto file_path = data_dir / (case_name + ".json");
            std::ifstream file(file_path);
            const json data = json::parse(file);
            file.close();
            const auto input = BasicInput{data.at("input").get<nlohmann::json>()};
            const auto expected = data.at("output").get<nlohmann::json>();
            // allocate
            auto algorithm = LargestFitFirst(input);
            algorithm.allocate();
            // check
            const auto output = algorithm.to_json();
            CHECK(output == expected);
        }
    }
}
