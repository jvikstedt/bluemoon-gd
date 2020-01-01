cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 14)

project(bluemoon)

find_library(GODOT_CPP_LIBRARY NAMES godot-cpp.linux.release.64 PATHS godot-cpp/bin)
find_library(mbedtls NAMES mbedtls)
find_library(mbedcrypto NAMES mbedcrypto)
find_library(sodium NAMES sodium)
find_library(mbedx509 NAMES mbedx509)

ADD_LIBRARY(gdbluemoon SHARED
  src/client/gdbluemoon.cpp
  src/client/library.cpp
  yojimbo/yojimbo.cpp
  yojimbo/tlsf/tlsf.c
  yojimbo/netcode.io/netcode.c
  yojimbo/reliable.io/reliable.c
)

target_include_directories(gdbluemoon PRIVATE
  godot-cpp/include
  godot-cpp/include/core
  godot-cpp/include/gen
  godot-cpp/godot_headers
  yojimbo
  yojimbo/tlsf
  yojimbo/netcode.io
  yojimbo/reliable.io
)

target_link_libraries(gdbluemoon
  ${GODOT_CPP_LIBRARY}
  mbedtls
  mbedcrypto
  sodium
  mbedx509
)

install(TARGETS gdbluemoon DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/game/bin/x11)
