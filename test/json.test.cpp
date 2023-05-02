#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <fstream>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

const auto data_dir = std::filesystem::path("test/data/json/");

TEST_CASE("read file", "[json]") {
    const auto file_path = data_dir / "01.json";
    std::ifstream file(file_path);
    const json data = json::parse(file);
    CHECK(data["id"].get<std::string>() == "6451902d4c88d542fa080f6b");
    CHECK(data["index"].get<unsigned>() == 25u);
    file.close();
}
