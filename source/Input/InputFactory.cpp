#include "Input/InputFactory.hpp"

#include <fstream>
#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>

#include "Input/Input_V_0_3_0.hpp"

namespace packing {

auto InputFactory::create(const std::string file_path) -> InputPtr {
    const nlohmann::json data = load_json(file_path);
    const auto version = data.at("version").get<std::string>();
    if (version == "0.3.0") {
        return std::make_unique<Input_V_0_3_0>(data);
    } else {
        throw std::runtime_error{"Invalid input version: " + version};
    }
}

auto InputFactory::load_json(const std::string file_path) -> nlohmann::json {
    std::ifstream file(file_path);
    const nlohmann::json data = nlohmann::json::parse(file);
    file.close();
    return data;
}

} // namespace packing
