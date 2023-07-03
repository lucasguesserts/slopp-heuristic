#include "Input/Input.hpp"

#include <fstream>
#include <stdexcept>
#include <string>

namespace packing {

Input::Input(const nlohmann::json & data)
    : data(data) {}

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
