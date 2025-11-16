#include "mcp_server.h"
#include "mcp_tool.h"
#include "mcp_resource.h"
#include "httplib.h"
#include "APIRequest.h"
#include "APIResponse.h"
#include "k_investment_api.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <filesystem>
#include <algorithm>
#include <json.hpp>
#include <cstdlib>

using json = nlohmann::json;

namespace handler {

mcp::json setStockConnection_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json getAccountInfo_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json getStockPrice_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json StockOrder_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json getOrderDetail_handler(const mcp::json& params, const std::string& /* session_id */);


} // namespace handler