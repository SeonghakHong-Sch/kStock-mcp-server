cmake_minimum_required(VERSION 3.10)
project(kStock-mcp
        VERSION 0.1.0
        DESCRIPTION "투자도우미 mcp"
        LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Threads REQUIRED)

#ssl 옵션 켜져있는지 검사
if(MCP_SSL)
    find_package(OpenSSL 3.0.0 COMPONENTS Crypto SSL REQUIRED)
    include_directories(${OPENSSL_INCLUDE_DIR}) # before including cpp-httplib to avoid OpenSSL with lower version included 
    message(STATUS "OpenSSL include directory: ${OPENSSL_INCLUDE_DIR}")
    add_compile_definitions(MCP_SSL CPPHTTPLIB_OPENSSL_SUPPORT)
endif()

#include 헤더파일, cpp-mcp sdk 포함
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cpp-mcp/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cpp-mcp/common)

# build MCP, 근데 example이랑 test 불필요한거 제외
set(MCP_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cpp-mcp)
add_library(mcp STATIC
    ${MCP_LIB_DIR}/src/mcp_message.cpp
    ${MCP_LIB_DIR}/src/mcp_resource.cpp
    ${MCP_LIB_DIR}/src/mcp_server.cpp
    ${MCP_LIB_DIR}/src/mcp_tool.cpp
    ${MCP_LIB_DIR}/src/mcp_stdio_client.cpp
    ${MCP_LIB_DIR}/src/mcp_sse_client.cpp
)

#mcp 라이브러리 타겟 헤더 적용
target_include_directories(mcp PUBLIC
    ${MCP_LIB_DIR}/include
    ${MCP_LIB_DIR}/common
)
target_include_directories(mcp PUBLIC Threads:Threads)


if(MCP_SSL)
    target_link_libraries(mcp PUBLIC OpenSSL::SSL OpenSSL::Crypto)
endif()

# build
add_executable(${PROJECT_NAME} server.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE mcp)