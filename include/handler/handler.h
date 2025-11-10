#include "mcp_tool.h"
#include "mcp_resource.h"

#include <iostream>
#include <string>

using json = nlohmann::json;

namespace handler {

mcp::json setStockConnection_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json getAccountInfo_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json getStockPrice_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json StockOrder_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json getOrderDetail_handler(const mcp::json& params, const std::string& /* session_id */);


} // namespace handler