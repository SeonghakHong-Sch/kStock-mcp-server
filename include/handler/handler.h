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
#include <future>
#include <vector>

using json = nlohmann::json;

namespace handler {

mcp::json set_stock_connection_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json get_accountinfo_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json get_stockprice_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json get_financial_info_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json get_stock_info_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json get_itemchart_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json order_stock_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json get_investor_trend_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json disconnect_stock_handler(const mcp::json& params, const std::string& /* session_id */);


} // namespace handler