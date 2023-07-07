#include "SmallItem/Specialization/SmallItemWithSurface.hpp"
#include "Test/Test.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <itertools.hpp>
#include <nlohmann/json.hpp>

#include "Algorithm/LargestFitFirstV2.hpp"
#include "Input/Specialization/BasicInput.hpp"

using json = nlohmann::json;

using namespace packing;
using namespace packing::algorithm;

const auto data_dir = std::filesystem::path("test/data/LargestFitFirstV2/");

TEST_CASE("all cases", "[LargestFitFirstV2]") {
    // data
    const auto cases = std::vector<std::string>{"01", "02", "03", "04"};
    for (const auto & case_name : cases) {
        SECTION("case " + case_name) {
            const auto file_path = data_dir / (case_name + ".json");
            std::ifstream file(file_path);
            const json data = json::parse(file);
            file.close();
            auto input = BasicInput<SmallItemWithSurface>{data.at("input").get<nlohmann::json>()};
            const auto expected = data.at("output").get<nlohmann::json>();
            // allocate
            auto algorithm = LargestFitFirstV2(input);
            algorithm.allocate();
            // check
            const auto output = algorithm.to_json();
            CHECK(output == expected);
        }
    }
}
