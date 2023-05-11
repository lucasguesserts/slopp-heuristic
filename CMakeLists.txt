CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

project(
    slopp-heuristic
    VERSION 0.0.0
    HOMEPAGE_URL "https://github.com/lucasguesserts/slopp-heuristic"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic-errors -fmax-errors=1 -Wno-error=ignored-qualifiers")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

include(cmake/CPM.cmake)
CPMAddPackage("gh:nlohmann/json@3.11.2")
CPMAddPackage("gh:catchorg/Catch2@3.3.2")
CPMAddPackage("gh:ryanhaining/cppitertools@2.1")

set(PROJECT_LIBRARY ${PROJECT_NAME})
set(HEADER_DIR ${CMAKE_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)

include_directories(${HEADER_DIR})

set(
    PROJECT_SOURCE_FILES
    ${SOURCE_DIR}/Vector3D.cpp
    ${SOURCE_DIR}/BoolCuboid.cpp
    ${SOURCE_DIR}/SmallItem.cpp
    ${SOURCE_DIR}/AllocatedSmallItem.cpp
    ${SOURCE_DIR}/LargeObject.cpp
    ${SOURCE_DIR}/SmallItemQuantityManager.cpp
    ${SOURCE_DIR}/LargestFitFirstAlgorithm.cpp
)

add_library(${PROJECT_LIBRARY} SHARED ${PROJECT_SOURCE_FILES})
target_link_libraries(${PROJECT_LIBRARY} boost_timer boost_chrono nlohmann_json::nlohmann_json Catch2::Catch2WithMain cppitertools::cppitertools)

add_executable(solve source/solve.cpp)
target_link_libraries(solve PRIVATE ${PROJECT_LIBRARY})

enable_testing()
add_subdirectory(test)
add_subdirectory(benchmark)

message("\n")
message("---- Project ${PROJECT_NAME} ----")
message("Version               = ${PROJECT_VERSION}")
message("Homepage              = ${PROJECT_HOMEPAGE_URL}")
message("C++ compiler          = ${CMAKE_CXX_COMPILER}")
message("Compiler version      = ${CMAKE_CXX_COMPILER_VERSION}")
message("Compiler flags        = ${CMAKE_CXX_FLAGS}")
message("\n")
