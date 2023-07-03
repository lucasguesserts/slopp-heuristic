#include "Input.hpp"

#include <fstream>
#include <string>

namespace packing {

Input::Input(const std::string file_path)
    : data(load_json(file_path)) {}

auto Input::type() const -> InputType {
    const auto type = this->data.at("type").get<std::string>();
    if (type == "input") {
        return InputType::INPUT;
    } else if (type == "output") {
        return InputType::OUTPUT;
    } else {
        throw std::runtime_error{"Invalid input type: " + type};
    }
}

auto Input::version() const -> InputVersion {
    const auto version = data.at("version").get<std::string>();
    if (version == "0.3.0") {
        return InputVersion::V_0_3_0;
    } else {
        throw std::runtime_error{"Invalid input version: " + version};
    }
}

auto Input::load_json(const std::string file_path) -> nlohmann::json {
    std::ifstream file(file_path);
    const nlohmann::json data = nlohmann::json::parse(file);
    file.close();
    return data;
}

} // namespace packing
