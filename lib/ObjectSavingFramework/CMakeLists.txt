#######################
#   General Settings  #
#######################

cmake_minimum_required(VERSION 3.9.2)
project(ObjectSavingFramework)

# Compiler flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb -pg")

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
target_include_directories(ObjectSavingFramework PRIVATE
	include)


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

option(EXAMPLES "Should an executable example be build" ON)
if (EXAMPLES)
	add_executable(ObjectSavingFrameworkExample ${main})
	target_link_libraries(ObjectSavingFrameworkExample ObjectSavingFramework)
	target_include_directories(ObjectSavingFrameworkExample PRIVATE
		include)
endif (EXAMPLES)
