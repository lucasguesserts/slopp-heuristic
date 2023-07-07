#ifndef INPUT_HPP_
#define INPUT_HPP_

#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <nlohmann/json.hpp>

#include "Type/Quantity.hpp"

namespace packing {

enum class InputVersion {
    V_0_3_0
};

template <typename ItemType, typename LargeObjectType>
class Input {
public:
    Input(const std::string file_path)
        : Input(Input::load_json(file_path)){};

    Input(const nlohmann::json data)
        : data(std::move(data)) {
        if (data.at("type").get<std::string>() != "input") {
            throw std::runtime_error{"Invalid input type: " + data.at("type").get<std::string>()};
        }
        return;
    };

    virtual ~Input() = default;

    virtual auto version() const -> InputVersion = 0;

    auto large_object() -> LargeObjectType {
        if (!_large_object) {
            _large_object = this->read_large_object(data.at("large_object"));
        }
        return *_large_object;
    }

    auto small_items() -> std::vector<std::shared_ptr<ItemType>> {
        if (_small_items.empty()) {
            for (const auto & small_item_data : data.at("small_items")) {
                _small_items.push_back(this->read_small_item(small_item_data));
            }
        }
        return _small_items;
    }

protected:
    const nlohmann::json data;

    std::vector<std::shared_ptr<ItemType>> _small_items;
    std::shared_ptr<LargeObjectType> _large_object;

    static auto load_json(const std::string file_path) -> nlohmann::json {
        std::ifstream file(file_path);
        const nlohmann::json data = nlohmann::json::parse(file);
        file.close();
        return data;
    }

    virtual auto read_small_item(const nlohmann::json & small_item_data) const -> std::shared_ptr<ItemType> = 0;
    virtual auto read_large_object(const nlohmann::json & large_object_data) const -> std::shared_ptr<LargeObjectType> = 0;
};

} // namespace packing

#endif
