cmake_minimum_required(VERSION 3.14)

# set the project name and version
project(p2p VERSION 0.1)

## specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.12.0
)

FetchContent_MakeAvailable(nlohmann_json)


add_executable(device
  main.cpp
  ntil.cpp
)

target_include_directories(device PRIVATE
  ../common/include
  ../common/lib_x86_linux/c2c-src/include
)

target_link_directories(device PRIVATE
  ../common/lib_x86_linux/ZLIB-ubuntu/static
)

target_link_libraries(device PRIVATE
  nlohmann_json::nlohmann_json
  c2c
  netcpi
  wincmpt
)
