#######################
#   General Settings  #
#######################

cmake_minimum_required(VERSION 3.5.1)
project(GroceriesInsight)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Compiler flags
set (CMAKE_CXX_STANDARD 11)

#######################
#      Libraries      #
#######################

add_subdirectory(lib/ObjectSavingFramework)
add_subdirectory(lib/googletest)

#######################
#     Executable      #
#######################


# Source Files
set(source_files
	src/product.cpp
	src/productservice.cpp
	src/transaction.cpp
	src/transactionservice.cpp
	src/ui/console/consolepage.cpp
	# TODO: Why do I need to add this?
	lib/ObjectSavingFramework/src/DataGatherer.cpp
)
set(main src/main.cpp)

# TODO: Why does this work, but the target_include_directories not?
include_directories(lib/ObjectSavingFramework/src)

add_executable(GroceriesInsight ${main} ${source_files})
target_include_directories(GroceriesInsight PRIVATE 
	lib/ObjectSavingFramework/src
	src)
target_link_libraries(GroceriesInsight ObjectSavingFramework)

#######################
#        Tests        #
#######################

# Create Tests
set(test_files
	test/producttest.cpp
	test/productservicetest.cpp
	test/transactiontest.cpp
	test/transactionservicetest.cpp
)

add_executable(GroceriesInsightTest ${source_files} ${test_files})
target_include_directories(GroceriesInsightTest PRIVATE 
	src
	lib
	lib/googletest/googletest/include)
target_link_libraries(GroceriesInsightTest gtest_main)