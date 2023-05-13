#include "Test.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <itertools.hpp>
#include <nlohmann/json.hpp>

#include "AllocatedSmallItem.hpp"
#include "LargeObject.hpp"
#include "LargestFitFirstAlgorithm.hpp"
#include "SmallItem.hpp"
#include "SmallItemQuantityManager.hpp"
#include "Vector3D.hpp"

using json = nlohmann::json;

using namespace packing;

const auto data_dir = std::filesystem::path("test/data/LargestFitFirstAlgorithm/");

TEST_CASE("all cases", "[LargestFitFirstAlgorithm]") {
    // data
    const auto cases = std::vector<std::string>{"01", "02", "03", "04"};
    for (const auto & case_name : cases) {
        SECTION("case " + case_name) {
            const auto file_path = data_dir / (case_name + ".json");
            std::ifstream file(file_path);
            const json data = json::parse(file);
            file.close();
            // allocate
            auto algorithm = LargestFitFirstAlgorithm(data["input"]);
            algorithm.allocate();
            // check
            const auto output = algorithm.to_json();
            CHECK(output == data["output"]);
        }
    }
}
