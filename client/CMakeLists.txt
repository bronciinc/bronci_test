cmake_minimum_required (VERSION 3.10)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("client")

add_executable (client
  "client.cpp"
  "client.h"
  "Interface.cpp"
)

if(WIN32)
  target_include_directories(client PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/lib_x86_win/c2c-src/include
  )

  target_link_directories(client PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/lib_x86_win/ZLIB-windows/static/win64
  )

  target_link_libraries(client PRIVATE
    c2c
    wincmpt
    netcpi
  )
else()
  target_include_directories(client PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/lib_x86_linux/c2c-src/include
  )

  target_link_directories(client PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/lib_x86_linux/ZLIB-ubuntu/static
  )

  target_link_libraries(client PRIVATE
    c2c
    wincmpt
    netcpi
    pthread
    rt
    dl
    m
  )
endif()

target_compile_definitions(client PRIVATE
  _CRT_SECURE_NO_WARNINGS
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET client PROPERTY CXX_STANDARD 20)
endif()
