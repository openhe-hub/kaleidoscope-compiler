cmake_minimum_required(VERSION 3.16)
project(kaleidoscope_compiler)

set(CMAKE_CXX_STANDARD 14)

set(source_list src/main.cpp
        src/lexer/Lexer.cpp
        src/ast/ExprAST.cpp)
include_directories(include)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(kaleidoscope_compiler ${source_list})

llvm_map_components_to_libnames(llvm_libs core orcjit native)
target_link_libraries(kaleidoscope_compiler ${llvm_libs})

message(STATUS "Find ${llvm_libs}")
