#######################
#   General Settings  #
#######################

cmake_minimum_required(VERSION 3.5.1)
project(GroceriesInsight)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Compiler flags
set (CMAKE_CXX_STANDARD 11)


#######################
#     Executable      #
#######################

# Source Files
set(source_files
	src/console.cpp
	src/product.cpp
	src/productservice.cpp
)
set(main src/main.cpp)

add_executable(GroceriesInsight ${main} ${source_files})


#######################
#        Tests        #
#######################

add_subdirectory(lib/googletest)

# Create Tests
set(test_files
	lib/fakeit/fakeit.hpp
	test/producttest.cpp
	test/productservicetest.cpp
)

add_executable(GroceriesInsightTest ${source_files} ${test_files})
target_include_directories(GroceriesInsightTest PUBLIC 
	src
	lib
	lib/googletest/googletest/include)
target_link_libraries(GroceriesInsightTest gtest_main)