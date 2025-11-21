#include "mcp_sse_client.h"
#include "json.hpp"
#include <iostream>
#include <string>

using json = nlohmann::json;

int main() {


    // Create a client
    mcp::sse_client client("http://localhost:8888");

    // Set capabilities
    mcp::json capabilities = {
        {"roots", {{"listChanged", true}}}
    };
    client.set_capabilities(capabilities);

    // Set timeout
    client.set_timeout(10);

    try {
        // Initialize the connection
        std::cout << "Initializing connection to MCP server..." << std::endl;
        bool initialized = client.initialize("ResourceTestClient", mcp::MCP_VERSION);

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
        mcp::json server_capabilities = client.get_server_capabilities();
        std::cout << "Server capabilities: " << server_capabilities.dump(4) << std::endl;

        // Check if resources are supported
        if (!server_capabilities.contains("resources")) {
            std::cerr << "Server does not support resources!" << std::endl;
            return 1;
        }

        std::cout << "\n=== Server supports resources! ===" << std::endl;

        // List available resources
        std::cout << "\n=== Listing available resources ===" << std::endl;
        try {
            auto resources = client.list_resources()["resources"];
            std::cout << "Available resources (" << resources.size() << " total):" << std::endl;
            
            for (const auto& resource : resources) {
                std::cout << "\n--- Resource ---" << std::endl;
                std::cout << "URI: " << resource["uri"] << std::endl;
                std::cout << "Name: " << resource["name"] << std::endl;
                std::cout << "MIME Type: " << resource["mimeType"] << std::endl;
                std::cout << "Description: " << resource["description"] << std::endl;
            }
        } catch (const mcp::mcp_exception& e) {
            std::cerr << "Error listing resources: " << e.what() << std::endl;
        }

        // Read stock_codes.json resource
        std::cout << "\n=== Reading stock_codes.json resource ===" << std::endl;
        try {
            // Try different possible URIs
            std::vector<std::string> possible_uris = {
                "file://./data/stock_codes.json",
                "file:///home/hongseonghak/kStock-mcp/data/stock_codes.json",
                "./data/stock_codes.json"
            };

            bool found = false;
            for (const auto& uri : possible_uris) {
                try {
                    std::cout << "\nTrying URI: " << uri << std::endl;
                    auto content = client.read_resource(uri);

                    std::cout << "✓ Successfully read resource!" << std::endl;
                    std::cout << "Content type: " << content.dump().substr(0, 100) << "..." << std::endl;

                    // Parse and display some stock codes
                    if (content.is_array() && content.size() > 0) {
                        std::cout << "\n=== Sample stock codes (first 5) ===" << std::endl;
                        for (size_t i = 0; i < std::min(size_t(5), content.size()); ++i) {
                            std::cout << content[i].dump(2) << std::endl;
                        }
                        std::cout << "\nTotal stock codes: " << content.size() << std::endl;
                    } else if (content.is_object()) {
                        std::cout << "\n=== Stock codes data ===" << std::endl;
                        std::cout << content.dump(2) << std::endl;
                    } else {
                        std::cout << "\nRaw content:\n" << content.dump(4) << std::endl;
                    }

                    found = true;
                    break;
                } catch (const mcp::mcp_exception& e) {
                    std::cout << "✗ Failed: " << e.what() << std::endl;
                }
            }

            if (!found) {
                std::cerr << "\n⚠ Could not read stock_codes.json with any URI" << std::endl;
            }

        } catch (const mcp::mcp_exception& e) {
            std::cerr << "Error reading resource: " << e.what() << std::endl;
        }

        // Test resource subscription (if supported)
        std::cout << "\n=== Testing resource subscription ===" << std::endl;
        if (server_capabilities["resources"].contains("subscribe") &&
            server_capabilities["resources"]["subscribe"].get<bool>()) {
            std::cout << "Server supports resource subscription" << std::endl;
            // Add subscription test here if needed
        } else {
            std::cout << "Server does not support resource subscription" << std::endl;
        }

    } catch (const mcp::mcp_exception& e) {
        std::cerr << "MCP error: " << e.what() << " (code: " << static_cast<int>(e.code()) << ")" << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\n✓ Resource test completed successfully" << std::endl;
    return 0;
}
