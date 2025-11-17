#include "handler.h"


using json = nlohmann::json;
using API = KInvestmentAPI::KInvestmentAPI;

namespace handler {

mcp::json setStockConnection_handler(const mcp::json& params, const std::string& /* session_id */) {
    auto api = API::getInstance();
    json config = {
        {"base_url", "https://openapi.koreainvestment.com:9443"},
        {"appkey", std::getenv("K_appkey")},
        {"appsecret", std::getenv("K_appsecret")}
    };
    api->setClient(config);
    api->setAccessToken();
    return {
        {
            {"type", "text"},
            {"text", "StockConnection Complete"}
        }
    };
}

mcp::json getAccountInfo_handler(const mcp::json& params, const std::string& /* session_id */) {
    
    auto api = API::getInstance();
    std::cout << params.dump(4) << std::endl;
    const std::string request_id = params["request_id"].is_string()
        ? params["request_id"].get<std::string>()
        : std::to_string(params["request_id"].get<int>());
    std::cout << request_id << std::endl;
    APIRequest::AccountInfoRequest account_request(request_id);
    APIResponse::AccountInfoResponse account_response(request_id);

    account_request.setRequestInfo(
        {
            {"content-type", "application/json; charset=utf-8"},
            {"custtype", "P"},
            {"CANO", std::getenv("K_cano")},
            {"ACNT_PRDT_CD", std::getenv("K_cano2")},
            {"INQR_DVSN", "02"},
            {"FUND_STTL_ICLD_YN", "Y"},
            {"PRCS_DVSN", "00"}
        }
    );

    json req, res;
    
    req = account_request.getRequestInfo();
    
    api->request_k_stock(req, res, 0);
    std::cout << res.dump(4);
    account_response.setResponseInfo(res);
    
    std::cout << account_response.getResponseInfo().dump(4) << std::endl;
    return {
        {
            {"type", "text"},
            {"text", res.dump()}
        }
    };


}

mcp::json getStockPrice_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json StockOrder_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json getOrderDetail_handler(const mcp::json& params, const std::string& /* session_id */);


} //namespace handler