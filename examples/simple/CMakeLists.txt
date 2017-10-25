cmake_minimum_required(VERSION 2.8)
project(LOGOL_SIMPLE)

include_directories(${LOGOL_SOURCE_DIR}/include)

# Add lib
LINK_DIRECTORIES(${LOGOL_BINARY_DIR})
set( DEPS "${DEPS};logol" )

# Global shit
file (GLOB_RECURSE LOGOL_SIMPLE_SRC ./*.cc)
add_executable(logol_simple ${LOGOL_SIMPLE_SRC})

target_link_libraries ( logol_simple ${DEPS} )
