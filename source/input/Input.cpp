#include "input/Input.hpp"

#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>

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

} // namespace packing
