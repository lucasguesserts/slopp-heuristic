#include <csignal>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include <nlohmann/json.hpp>

#include "LargestFitFirstAlgorithm.hpp"

using json = nlohmann::json;

using namespace packing;

#if __clang__
#pragma clang diagnostic ignored "-Wunused-parameter"
#endif

auto input_file_path = std::filesystem::path();
auto output_file_path = std::filesystem::path();
std::unique_ptr<LargestFitFirstAlgorithm> algorithm;

void make_output() {
    const auto output = algorithm->to_json();
    std::ofstream output_file(output_file_path);
    output_file << output.dump(2);
    output_file.close();
}

void handler(int signal) {
    make_output();
    exit(signal);
}

auto main(int argc, char * argv[]) -> int {
    // CLI args
    const auto program_name = std::string(argv[0]);
    if (argc != 3) {
        std::cerr
            << "Usage:" << std::endl
            << "    " << program_name << " INPUT"
            << " "
            << "OUTPUT" << std::endl
            << "    "
            << "INPUT is a json file specifying the input of the problem" << std::endl
            << "    "
            << "OUTPUT is the file to save the output" << std::endl;
        return 1;
    }
    input_file_path = std::filesystem::path(argv[1]);
    output_file_path = std::filesystem::path(argv[2]);
    const auto output_dir = output_file_path.parent_path();
    std::filesystem::create_directories(output_dir);

    // input data
    std::ifstream input_file(input_file_path);
    const json data = json::parse(input_file);
    input_file.close();

    // solve
    algorithm = std::make_unique<LargestFitFirstAlgorithm>(data);
    signal(SIGINT, handler);
    signal(SIGTERM, handler);
    algorithm->allocate();

    // output
    make_output();

    exit(0);
}
