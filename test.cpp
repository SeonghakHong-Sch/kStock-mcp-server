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

#ifndef DATA_DIR
#define DATA_DIR "./data"
#endif

using json = nlohmann::json;
using API = KInvestmentAPI::KInvestmentAPI;


int main() {

    std::filesystem::create_directories("./files");
    
    // Create and configure server
    mcp::server::configuration srv_conf;
    //srv_conf.host = "localhost";
    srv_conf.host = "0.0.0.0"; //wsl용
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
        {"tools", mcp::json::object()},
        {"resources", {{"subscribe", false}, {"listChanged", true}}}
    };
    server.set_capabilities(capabilities);
    
    // Register tools
    mcp::tool set_stock_connection_tool = mcp::tool_builder("set_connection_stock")
        .with_description("set Korean Stock API connection. This tool most be excuted as first")
        .build();
    
    mcp::tool get_accountinfo_tool = mcp::tool_builder("get_account_info")
        .with_description("Get user's account info")
        .build();
    
    mcp::tool disconnect_stock_tool = mcp::tool_builder("set_disconnection_stock")
        .with_description("disconnect Stock")
        .build();

    mcp::tool get_stockprice_tool = mcp::tool_builder("get_stock_price")
        .with_description("get stock price")
        .with_string_param("FID_COND_MRKT_DIV_CODE", "condition market division code")
        .with_string_param("FID_INPUT_ISCD", "ticker")
        .build();

    mcp::tool get_fin_info_tool = mcp::tool_builder("get_financial_info")
        .with_description("get korean stockmarket financial info")
        .with_string_param("FID_DIV_CLS_CODE", "0: year, 1: quarter")
        .with_string_param("fid_cond_mrkt_div_code", "market division code: J")
        .with_string_param("fid_input_iscd", "ticker")
        .build();

    mcp::tool get_stock_info_tool = mcp::tool_builder("get_stock_info")
        .with_description("get korean stock info")
        .with_string_param("PDNO", "ticker, if ETN, start with Q(EX. Q500001)")
        .build();

    mcp::tool get_itemchart_tool = mcp::tool_builder("get_itemchart")
        .with_description("get inquire-daily itemchart price")
        .with_string_param("FID_COND_MRKT_DIV_CODE", "condition market division code")
        .with_string_param("FID_INPUT_ISCD", "ticker")
        .with_string_param("FID_INPUT_DATE_1", "start date")
        .with_string_param("FID_INPUT_DATE_2", "end date, max: 100")
        .with_string_param("FID_PERIOD_DIV_CODE", "D: Daily, W: Weekly, M: Monthly, Y: Yearly")
        .with_string_param("FID_ORG_ADJ_PRC", "0: Adjusted price, 1: Original price")
        .build();

    mcp::tool order_stock_tool = mcp::tool_builder("order_stock")
        .with_description("order korean stock(buy, sell)")
        .with_string_param("ORD_TYPE", "Order type. B: buy, S: Sell")
        .with_string_param("PDNO", "ticker")
        .with_string_param("SLL_TYPE", "sell type. used only sell orders. 00(default): 일반매도, 02: dladmlaoao, 05(대차매도)", false)
        .with_string_param("ORD_DVSN", "order type")
        .with_string_param("ORD_QTY", "order quantity")
        .with_string_param("ORD_UNPR", "order price, the price per share. 0: market price")
        .with_string_param("CNDT_PRIC", "stop condition price. required when only ORD_DVSN = 22", false)
        .build();

    mcp::tool get_investor_trend_tool = mcp::tool_builder("get_investor_trend")
        .with_description("get investor trading trend by ticker")
        .with_string_param("FID_COND_MRKT_DIV_CODE", "condition market division code")
        .with_string_param("FID_INPUT_ISCD", "ticker")
        .with_string_param("FID_INPUT_DATE_1", "date (YYYYMMDD)")
        .build();

    // Register tool
    server.register_tool(set_stock_connection_tool, handler::set_stock_connection_handler);
    server.register_tool(get_accountinfo_tool, handler::get_accountinfo_handler);
    server.register_tool(disconnect_stock_tool, handler::disconnect_stock_handler);
    server.register_tool(get_stockprice_tool, handler::get_stockprice_handler);
    server.register_tool(get_fin_info_tool, handler::get_financial_info_handler);
    server.register_tool(get_stock_info_tool, handler::get_stock_info_handler);
    server.register_tool(get_itemchart_tool, handler::get_itemchart_handler);
    server.register_tool(order_stock_tool, handler::order_stock_handler);
    server.register_tool(get_investor_trend_tool, handler::get_investor_trend_handler);

    // Register resources
    const std::string path = std::string(DATA_DIR) + "/stock_codes.json";
    auto file_resource = std::make_shared<mcp::file_resource>(
        path,
        "application/json",
        "Korean stock codes");
    server.register_resource("file://" + path, file_resource);

    // Start server
    std::cout << "Starting MCP server at " << srv_conf.host << ":" << srv_conf.port << std::endl;
    std::cout << "Press Ctrl+C to stop the server" << std::endl;
    server.start(true);  // Blocking mode


    
    return 0;
}
