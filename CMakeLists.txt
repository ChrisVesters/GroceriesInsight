# General Information
cmake_minimum_required(VERSION 3.5.1)
project(GroceriesInsight)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Compiler flags
set (CMAKE_CXX_STANDARD 11)

# Add Libaries
set(INSTALL_GTEST ON)
add_subdirectory(lib/googletest)

# Source Files
set(source_files
	src/console.cpp
	src/product.cpp
	src/productservice.cpp
)
set(main src/main.cpp)

add_executable (GroceriesInsight ${main} ${source_files})


include_directories(${GTEST_INCLUDE_DIRS})

set(test_files
	test/producttest.cpp
	test/productservicetest.cpp
)

add_executable(GroceriesInsightTest ${source_files} ${test_files})
target_include_directories(GroceriesInsightTest PUBLIC src lib/googletest/googletest/include)
target_link_libraries(GroceriesInsightTest gtest_main)