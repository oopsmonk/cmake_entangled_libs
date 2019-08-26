#[[
Copyright (c) 2019 IOTA Stiftung

Refer to the LICENSE file for licensing information
]]

cmake_minimum_required(VERSION 3.5)

project(test_cclient)

include(ExternalProject)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# we build and install on a sandbox.
set(CMAKE_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/install" CACHE PATH "..." FORCE)

set(INSTALL_PATH "${PROJECT_BINARY_DIR}/install")
ExternalProject_Add(
  entangled
  DOWNLOAD_NAME entangled.tar.gz
  URL https://github.com/oopsmonk/entangled/archive/1cdfc9e1ea4e90e82e9d6da609e06664a20d61e2.tar.gz
  URL_HASH SHA256=79e7113ff901736d46642cfd5e3a5c8b5dad84a9c0b889c8e87d8020e9ba2361
  CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX:STRING=${INSTALL_PATH}
)

link_directories("${CMAKE_INSTALL_PREFIX}/lib")
add_executable(${PROJECT_NAME} test_cclient.c)

# header files location
target_include_directories(${PROJECT_NAME} PUBLIC 
  "${CMAKE_INSTALL_PREFIX}/include/entangled" # entangled headers
  "${CMAKE_INSTALL_PREFIX}/include" # external lib headers
)

add_dependencies(${PROJECT_NAME} entangled)

target_link_libraries(${PROJECT_NAME} 
  # entangled libs
  cclient 
  common
  # external libs
  cjson
  keccak
  mbedtls
  mbedcrypto
  mbedx509
  http_parser
  logger
  # pthread
  Threads::Threads
)
