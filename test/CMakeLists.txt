project(test)

set(TEST_EXECUTABLE "run_tests")

include_directories(${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/)

set(
    TEST_CASE_SOURCE_LIST
    Size.test.cpp
    BoolCuboid.test.cpp
    SmallItem.test.cpp
    LargeObject.test.cpp
    SmallItemQuantityManager.test.cpp
)

foreach(TEST_CASE_SOURCE IN ITEMS ${TEST_CASE_SOURCE_LIST})
    cmake_path(GET TEST_CASE_SOURCE STEM TEST_CASE_NAME)
    add_executable(${TEST_CASE_NAME} ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/${TEST_CASE_SOURCE})
    add_test(NAME ${TEST_CASE_NAME} COMMAND ${TEST_CASE_NAME} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
    target_link_libraries(${TEST_CASE_NAME} PRIVATE ${PROJECT_LIBRARY} PRIVATE Catch2::Catch2WithMain)
endforeach()
