#include "Test/Test.hpp"

#include "brkga_mp_ipr.hpp"

TEST_CASE("brkga", "[brkga]") {
    CHECK_FALSE(BRKGA::Sense::MINIMIZE == BRKGA::Sense::MAXIMIZE);
}
