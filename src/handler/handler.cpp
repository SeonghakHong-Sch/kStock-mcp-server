#include "handler.h"

#include <typeinfo>

using json = nlohmann::json;
using API = KInvestmentAPI::KInvestmentAPI;

namespace handler {

mcp::json set_stock_connection_handler(const mcp::json& params, const std::string& /* session_id */) {
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

mcp::json get_accountinfo_handler(const mcp::json& params, const std::string& /* session_id */) {
    
    auto api = API::getInstance();
    
    const std::string request_id = params["request_id"].is_string()
        ? params["request_id"].get<std::string>()
        : std::to_string(params["request_id"].get<int>());
    
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
    account_response.setResponseInfo(res);
    std::cout << typeid(res).name() << std::endl;
    return {
        {
            {"type", "text"},
            {"text", res.dump()}
        }
    };


}

mcp::json get_stockprice_handler(const mcp::json& params, const std::string& /* session_id */) {
    auto api = API::getInstance();

    std::cout << params.dump(4) << std::endl;
    const std::string request_id = params["request_id"].is_string()
        ? params["request_id"].get<std::string>()
        : std::to_string(params["request_id"].get<int>());
    std::cout << request_id << std::endl;
    APIRequest::StockPriceRequest stockprice_request(request_id);
    APIResponse::StockPriceResponse stockprice_response(request_id);

    stockprice_request.setRequestInfo(
        {
            {"content-type", "application/json; charset=utf-8"},
            {"custtype", "P"},
            {"FID_COND_MRKT_DIV_CODE", params["FID_COND_MRKT_DIV_CODE"]},
            {"FID_INPUT_ISCD", params["FID_INPUT_ISCD"]}
        }
    );

    json req, res;
    req = stockprice_request.getRequestInfo();

    std::cout << "Before request_k_stock" << std::endl;
    api->request_k_stock(req, res, 0);
    std::cout << "After request_k_stock, res type: " << res.type_name() << std::endl;
    std::cout << "res is_null: " << res.is_null() << ", is_object: " << res.is_object() << std::endl;

    if (!res.is_null()) {
        std::cout << "res dump: " << res.dump(4) << std::endl;
    }

    stockprice_response.setResponseInfo(res);
    std::cout << "resobj: " << stockprice_response.getResponseInfo().dump(4) << std::endl;
    return json::array({ 
        {
            {"type", "text"},
            {"text", res.dump()}
        }
    });
}

mcp::json StockOrder_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json getOrderDetail_handler(const mcp::json& params, const std::string& /* session_id */);

mcp::json disconnect_stock_handler(const mcp::json& params, const std::string& /* session_id */) {
    auto api = API::getInstance();
    api->revokeAccessToken();
    API::revokeInstance();
    return {
        {
            {"type", "text"},
            {"text", "Connection revoked"}
        }
    };
}


} //namespace handler