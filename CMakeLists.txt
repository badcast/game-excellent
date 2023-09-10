cmake_minimum_required(VERSION 3.0)

project(Excellent LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(RONIN_NO_CONFIG ON)

# ronin-engine-library
add_subdirectory(RoninEngine)

file(GLOB_RECURSE GAME_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

file(GLOB_RECURSE GAME_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.hpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/source/*.h")

add_executable(Excellent ${GAME_HEADERS} ${GAME_SOURCES})

set_target_properties(Excellent PROPERTIES OUTPUT_NAME game)

target_link_libraries(Excellent PRIVATE RoninEngine)

# create link resources "data:resources"
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(_DATA_DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data")
if(NOT EXISTS "${_DATA_DESTINATION}")
  message(STATUS "Linking data to \"${_DATA_DESTINATION}\"")
  file(CREATE_LINK "${CMAKE_CURRENT_SOURCE_DIR}/resources/data"
       "${_DATA_DESTINATION}" SYMBOLIC)
else()
  message(STATUS "Symbolic link exists - not required")
endif()
unset(_DATA_DESTINATION)
