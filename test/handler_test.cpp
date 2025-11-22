#include "mcp_sse_client.h"
#include "json.hpp"
#include <iostream>
#include <string>

using json = nlohmann::json;

int main() {
    // Create a client
    // mcp::sse_client client("https://localhost:8888", "/sse", true, "/etc/ssl/certs/ca-certificates.crt");
    // mcp::sse_client client("https://localhost:8888", "/sse", true, "./ca.cert.pem");
    mcp::sse_client client("http://localhost:8888");

    // Set capabilites
    mcp::json capabilities = {
        {"roots", {{"listChanged", true}}}
    };
    client.set_capabilities(capabilities);
    
    // Set timeout
    client.set_timeout(10);
    
    try {
        // Initialize the connection
        std::cout << "Initializing connection to MCP server..." << std::endl;
        bool initialized = client.initialize("ExampleClient", mcp::MCP_VERSION);
        
        if (!initialized) {
            std::cerr << "Failed to initialize connection to server" << std::endl;
            return 1;
        }

        // Ping the server
        std::cout << "Pinging server..." << std::endl;
        if (!client.ping()) {
            std::cerr << "Failed to ping server" << std::endl;
            return 1;
        }
        
        // Get server capabilities
        std::cout << "Getting server capabilities..." << std::endl;
        mcp::json capabilities = client.get_server_capabilities();
        std::cout << "Server capabilities: " << capabilities.dump(4) << std::endl;
        
        // Get available tools
        std::cout << "\n=== Getting available tools ===" << std::endl;
        auto tools = client.get_tools();
        std::cout << "Available tools:" << std::endl;
        for (const auto& tool : tools) {
            std::cout << "\nTool: " << tool.name << std::endl;
            std::cout << "Description: " << tool.description << std::endl;
            std::cout << "Parameters Schema: " << tool.parameters_schema.dump(2) << std::endl;
        }

        // 1. Test kStock-mcp tools
        std::cout << "\n=== Testing set_connection_stock ===" << std::endl;
        try {
            mcp::json account_result = client.call_tool("set_connection_stock");
            std::cout << "Success StockConnection" << std::endl;
        } catch (const mcp::mcp_exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }



        // 2. Test get_AccountInfo (계정 정보 조회 - 파라미터 없을 가능성 높음)
        std::cout << "\n=== Testing get_account_info ===" << std::endl;
        try {
            mcp::json account_params = {
                {"request_id", "1"}
            };
            mcp::json account_result = client.call_tool("get_account_info", account_params);
            std::cout << "Account Info: " << account_result.dump(2) << std::endl;
        } catch (const mcp::mcp_exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // 3. Test get_stockprice (주식 가격 조회)
        std::cout << "\n=== Testing get_stock_price ===" << std::endl;
        try {
            mcp::json price_params = {
                {"request_id", "test"},
                {"FID_COND_MRKT_DIV_CODE", "J"},
                {"FID_INPUT_ISCD", "005930"}  // 삼성전자 예시
            };
            mcp::json price_result = client.call_tool("get_stock_price", price_params);
            std::cout << "Stock Price: " << price_result.dump(2) << std::endl;
        } catch (const mcp::mcp_exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // 4. Test get_financial_info (주식 재무비율 조회)
        std::cout << "\n=== Testing get_financial_info ===" << std::endl;
        try {
            mcp::json finratio_params = {
                {"request_id", "test"},
                {"FID_DIV_CLS_CODE", "0"},
                {"fid_cond_mrkt_div_code", "J"},
                {"fid_input_iscd", "000660"}
            };
            mcp::json finratio_result = client.call_tool("get_financial_info", finratio_params);
            std::cout << "Fin Ratio: " << finratio_result.dump(2) << std::endl;
        } catch (const mcp::mcp_exception& e){
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // 5. Test get_stock_info (주식 기본정보 조회)
        std::cout << "\n=== Testing get_stock_info ===" << std::endl;
        try {
            mcp::json stockinfo_params = {
                {"request_id", "test"},
                {"PDNO", "000660"}
            };
            mcp::json stockinfo_result = client.call_tool("get_stock_info", stockinfo_params);
            std::cout << "Stock info: " << stockinfo_result.dump(2) << std::endl;
        } catch (const mcp::mcp_exception& e){
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // 6. Test get_itemchart_handler (주식 과거정보(일,주,월,년) 봉 조회)
                std::cout << "\n=== Testing get_itemchart_handler ===" << std::endl;
        try {
            mcp::json chart_params = {
                {"request_id", "test"},
                {"FID_COND_MRKT_DIV_CODE", "J"},
                {"FID_INPUT_ISCD", "005930"},
                {"FID_INPUT_DATE_1", "2025-01-01"},
                {"FID_INPUT_DATE_2", "2025-03-01"},
                {"FID_PERIOD_DIV_CODE", "D"},
                {"FID_ORG_ADJ_PRC", "1"}
            };
            mcp::json chart_result = client.call_tool("get_itemchart", chart_params);
            std::cout << "Chart info: " << chart_result.dump(2) << std::endl;
        } catch (const mcp::mcp_exception& e){
            std::cerr << "Error: " << e.what() << std::endl;
        }
        

        // 0. Test ~~


    } catch (const mcp::mcp_exception& e) { 
        std::cerr << "MCP error: " << e.what() << " (code: " << static_cast<int>(e.code()) << ")" << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\nClient example completed successfully" << std::endl;
    return 0;
}