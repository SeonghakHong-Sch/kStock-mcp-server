set(TARGET handler_test)

add_executable(${TARGET} handler_test.cpp)
add_executable(resource_test resource_test.cpp)


# Link MCP library
target_link_libraries(${TARGET} PRIVATE mcp)
target_link_libraries(resource_test PRIVATE mcp)

# Include MCP headers
target_include_directories(${TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../cpp-mcp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../cpp-mcp/common
)
target_include_directories(resource_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../cpp-mcp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../cpp-mcp/common
)

# Link OpenSSL if enabled
if(MCP_SSL)
    target_link_libraries(${TARGET} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
    target_link_libraries(resource_test PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()

# Link Threads
target_link_libraries(${TARGET} PRIVATE Threads::Threads)
target_link_libraries(resource_test PRIVATE Threads::Threads)
