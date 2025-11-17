/**
 * @file server_example.cpp
 * @brief Server example based on MCP protocol
 * 
 * This example demonstrates how to create an MCP server, register tools and resources,
 * and handle client requests. Follows the 2024-11-05 basic protocol specification.
 */
#include "k_investment_api.h"
#include "json.hpp"
#include "APIRequest.h"
#include "handler.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <filesystem>
#include <algorithm>
#include <json.hpp>
#include <cstdlib>

using json = nlohmann::json;
using API = KInvestmentAPI::KInvestmentAPI;


int main() {

    std::filesystem::create_directories("./files");
    
    // Create and configure server
    mcp::server::configuration srv_conf;
    //srv_conf.host = "localhost"; //linux용
    srv_conf.host = "0.0.0.0";
    srv_conf.port = 8888;
    // srv_conf.threadpool_size = 1;
    // srv_conf.ssl.server_cert_path = "./server.cert.pem";
    // srv_conf.ssl.server_private_key_path = "./server.key.pem";

    mcp::server server(srv_conf);
    server.set_server_info("ExampleServer", "1.0.0");
    
    // Set server capabilities
    // mcp::json capabilities = {
    //     {"tools", {{"listChanged", true}}},
    //     {"resources", {{"subscribe", false}, {"listChanged", true}}}
    // };
    mcp::json capabilities = {
        {"tools", mcp::json::object()}
    };
    server.set_capabilities(capabilities);
    
    // Register tools
    mcp::tool stockConnection_tool = mcp::tool_builder("stockConnection")
        .with_description("set Korean Stock API connection")
        .build();
    
    mcp::tool accountInfo_tool = mcp::tool_builder("get_AccountInfo")
        .with_description("Get user's account info")
        .build();
    
    
    
    server.register_tool(stockConnection_tool, handler::setStockConnection_handler);
    server.register_tool(accountInfo_tool, handler::getAccountInfo_handler);
    
    


    // Start server
    std::cout << "Starting MCP server at " << srv_conf.host << ":" << srv_conf.port << std::endl;
    std::cout << "Press Ctrl+C to stop the server" << std::endl;
    server.start(true);  // Blocking mode


    
    return 0;
}
