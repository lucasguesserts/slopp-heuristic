#ifndef INPUT_HPP_
#define INPUT_HPP_

#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "Type/Quantity.hpp"

namespace packing {

enum class InputVersion {
    V_0_3_0
};

template <typename ItemTypePtr, typename LargeObjectType>
class Input {
public:
    Input(const std::string file_path)
        : data(load_json(file_path)) {
        if (data.at("type").get<std::string>() != "input") {
            throw std::runtime_error{"Invalid input type: " + data.at("type").get<std::string>()};
        }
        return;
    };

    virtual ~Input() = default;

    virtual auto version() const -> InputVersion = 0;

    virtual auto large_object() const -> LargeObjectType = 0;
    virtual auto small_items() const -> std::vector<ItemTypePtr> = 0;

protected:
    const nlohmann::json data;

    auto load_json(const std::string file_path) -> nlohmann::json {
        std::ifstream file(file_path);
        const nlohmann::json data = nlohmann::json::parse(file);
        file.close();
        return data;
    }
};

} // namespace packing

#endif
