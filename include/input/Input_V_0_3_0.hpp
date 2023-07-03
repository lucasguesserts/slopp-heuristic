#ifndef INPUT_V_0_3_0_HPP_
#define INPUT_V_0_3_0_HPP_

#include "input/Input.hpp"

#include <nlohmann/json.hpp>

namespace packing {

class Input_V_0_3_0 : public Input {
public:
    Input_V_0_3_0(const nlohmann::json & data);
    ~Input_V_0_3_0() = default;
};

} // namespace packing

#endif
