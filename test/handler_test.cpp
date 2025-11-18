#include "mcp_sse_client.h"
#include <iostream>
#include <string>

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
        std::cout << "\n=== Testing stockConnection ===" << std::endl;
        try {
            mcp::json account_result = client.call_tool("set_stockConnection");
            std::cout << "Success StockConnection" << std::endl;
        } catch (const mcp::mcp_exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }



        // 2. Call get_AccountInfo (계정 정보 조회 - 파라미터 없을 가능성 높음)
        std::cout << "\n=== Testing get_AccountInfo ===" << std::endl;
        try {
            mcp::json account_params = {
                {"request_id", "1"}
            };
            mcp::json account_result = client.call_tool("get_AccountInfo", account_params);
            std::cout << "Account Info: " << account_result.dump(2) << std::endl;
        } catch (const mcp::mcp_exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // 3. Call get_stockprice (주식 가격 조회)
        std::cout << "\n=== Testing get_stockprice ===" << std::endl;
        try {
            mcp::json price_params = {
                {"request_id", "test"},
                {"FID_COND_MRKT_DIV_CODE", "J"},
                {"FID_INPUT_ISCD", "005930"}  // 삼성전자 예시
            };
            mcp::json price_result = client.call_tool("get_stockprice", price_params);
            std::cout << "Stock Price: " << price_result.dump(2) << std::endl;
        } catch (const mcp::mcp_exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
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