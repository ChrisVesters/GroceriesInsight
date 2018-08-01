#######################
#   General Settings  #
#######################

cmake_minimum_required(VERSION 3.5.1)
project(ObjectSavingFramework)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Compiler flags
set (CMAKE_CXX_STANDARD 11)


#######################
#     Executable      #
#######################

# Source Files
set(source_files
	src/DataGatherer.cpp
	src/ConsoleMapper.cpp
	src/XmlMapper.cpp
	src/JsonMapper.cpp
)

set(main example/Examples.cpp)

add_library(ObjectSavingFramework ${source_files})


#######################
#        Tests        #
#######################

# add_subdirectory(lib/googletest)

# Create Tests
set(test_files
)

# add_executable(GroceriesInsightTest ${source_files} ${test_files})
#target_include_directories(GroceriesInsightTest PUBLIC 
#	src
#	lib
#	lib/googletest/googletest/include)
#target_link_libraries(GroceriesInsightTest gtest_main)

#######################
#      Examples       #
#######################

option(EXAMPLES "Should an executable example be build" OFF)
if (EXAMPLES)
	add_executable(ObjectSavingFrameworkExample ${main})
	target_include_directories(ObjectSavingFrameworkExample PRIVATE 
		src)
	target_link_libraries(ObjectSavingFrameworkExample ObjectSavingFramework)
endif (EXAMPLES)
