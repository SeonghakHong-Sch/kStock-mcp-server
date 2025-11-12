set(API api/k_investment_api.cpp)
set(resreq 
    resreq/APIRequest.cpp
    resreq/APIResponse.cpp
)
add_library(kstock_lib STATIC
    ${API}
    ${resreq}
)

target_include_directories(kstock_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/api
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/handler
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/domain
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/processor
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/resreq
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/tool
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/utils
)

target_link_libraries(kstock_lib PUBLIC mcp)

if(MCP_SSL)
    target_link_libraries(kstock_lib PUBLIC OpenSSL::SSL OpenSSL::Crypto)
endif()