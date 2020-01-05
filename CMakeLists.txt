cmake_minimum_required(VERSION 3.16)
project(bluemoon)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(Yojimbo REQUIRED)
find_package(Mbedtls REQUIRED)
find_package(Sodium REQUIRED)
find_library(GODOT_CPP_LIBRARY NAMES godot-cpp.linux.release.64 PATHS godot-cpp/bin)

ADD_LIBRARY(gdbluemoon SHARED
  src/gd/gdbluemoon.cpp
  src/gd/library.cpp
  src/client/GameClient.cpp
  src/client/logger.cpp
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
  ${MBEDTLS_LIBRARIES}
  ${SODIUM_LIBRARY}
)

install(TARGETS gdbluemoon DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/game/bin/x11)

add_executable(bluemoon-server src/server/main.cpp
  src/server/GameServer.cpp
  src/server/ServerAdapter.cpp
)

target_link_libraries(bluemoon-server
  ${YOJIMBO_LIBRARY}
  ${MBEDTLS_LIBRARIES}
  ${SODIUM_LIBRARY}
)

target_include_directories(bluemoon-server PRIVATE
  yojimbo
)

add_executable(bluemoon-client src/client/main.cpp
  src/client/GameClient.cpp
  src/client/logger.cpp
)

target_link_libraries(bluemoon-client
  ${YOJIMBO_LIBRARY}
  ${MBEDTLS_LIBRARIES}
  ${SODIUM_LIBRARY}
)

target_include_directories(bluemoon-client PRIVATE
  yojimbo
)
