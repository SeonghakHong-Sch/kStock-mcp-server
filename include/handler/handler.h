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

mcp::json set_stock_connection_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json get_accountinfo_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json get_stockprice_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json get_financial_ratio(const mcp::json& params, const std::string& /* session_id */);

mcp::json StockOrder_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json disconnect_stock_handler(const mcp::json& params, const std::string& /* session_id */);


} // namespace handler