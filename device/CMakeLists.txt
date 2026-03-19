cmake_minimum_required(VERSION 3.14)

# set the project name and version
project(p2p VERSION 0.1)

## specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)


include(FetchContent)

FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.12.0
)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 11.2.0
)

FetchContent_MakeAvailable(nlohmann_json)
FetchContent_MakeAvailable(fmt)


add_executable(device
  main.cpp
  ntil.cpp
  libstdcxx_compat.cpp
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
  fmt::fmt-header-only
  Threads::Threads
  c2c
  netcpi
  wincmpt
)
