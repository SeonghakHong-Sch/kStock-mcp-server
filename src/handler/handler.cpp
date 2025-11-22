#include "handler.h"


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

    const std::string request_id = params["request_id"].is_string()
        ? params["request_id"].get<std::string>()
        : std::to_string(params["request_id"].get<int>());
    
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

    api->request_k_stock(req, res, 0);

    stockprice_response.setResponseInfo(res);
    
    return { 
        {
            {"type", "text"},
            {"text", res.dump()}
        }
    };
}


mcp::json get_financial_info_handler(const mcp::json& params, const std::string& /* session_id */) {
    auto api = API::getInstance();

    const std::string request_id = params["request_id"].is_string()
        ? params["request_id"].get<std::string>()
        : std::to_string(params["request_id"].get<int>());

    json request_info = {
        {"content-type", "application/json; charset=utf-8"},
        {"custtype", "P"},
        {"FID_DIV_CLS_CODE", params["FID_DIV_CLS_CODE"]},
        {"fid_cond_mrkt_div_code", params["fid_cond_mrkt_div_code"]},
        {"fid_input_iscd", params["fid_input_iscd"]}
    };
    json result;

    //api 요청 비동기 처리
    //대차대조표
    auto future_fin_balance = std::async(std::launch::async, [&]() {
        json req, res;

        APIRequest::FinInfoRequest fininfo_request(request_id);
        fininfo_request.setRequestInfo(request_info);
        fininfo_request.set_tr_id("FHKST66430100");
        fininfo_request.set_url("/uapi/domestic-stock/v1/finance/balance-sheet");

        req = fininfo_request.getRequestInfo();

        api->request_k_stock(req, res, 0);

        return res;
    });
    //손익계산서
    auto future_fin_income = std::async(std::launch::async, [&]() {
        json req, res;

        APIRequest::FinInfoRequest fininfo_request(request_id);
        fininfo_request.setRequestInfo(request_info);
        fininfo_request.set_tr_id("FHKST66430200");
        fininfo_request.set_url("/uapi/domestic-stock/v1/finance/income-statement");
        
        req = fininfo_request.getRequestInfo();

        api->request_k_stock(req, res, 0);

        return res;
    });
    //재무비율
    auto future_fin_ratio = std::async(std::launch::async, [&]() {
        json req, res;

        APIRequest::FinInfoRequest fininfo_request(request_id);
        fininfo_request.setRequestInfo(request_info);
        fininfo_request.set_tr_id("FHKST66430300");
        fininfo_request.set_url("/uapi/domestic-stock/v1/finance/financial-ratio");
        
        req = fininfo_request.getRequestInfo();

        api->request_k_stock(req, res, 0);

        return res;
    });

    result["fin_balance_list"] = future_fin_balance.get();
    result["fin_income_list"] = future_fin_income.get();
    result["fin_ratio_list"] = future_fin_ratio.get();

    APIResponse::FinInfoResponse fininfo_response(request_id);
    fininfo_response.setResponseInfo(result);

    return {
        {
            {"type", "text"},
            {"text", result.dump()}
        }
    };
}

mcp::json get_stock_info_handler(const mcp::json& params, const std::string& /* session_id */) {
    auto api = API::getInstance();

    const std::string request_id = params["request_id"].is_string()
        ? params["request_id"].get<std::string>()
        : std::to_string(params["request_id"].get<int>());

    APIRequest::StockInfoRequest stockinfo_request(request_id);
    APIResponse::StockInfoResponse stockinfo_response(request_id);

    stockinfo_request.setRequestInfo(
        {
            {"content-type", "application/json; charset=utf-8"},
            {"custtype", "P"},
            {"PDNO", params["PDNO"]}
        }
    );

    json req, res;
    req = stockinfo_request.getRequestInfo();

    api->request_k_stock(req, res, 0);

    stockinfo_response.setResponseInfo(res);

    return {
        {
            {"type", "text"},
            {"text", res.dump()}
        }
    };
}

mcp::json get_itemchart_handler(const mcp::json& params, const std::string& /* session_id */) {
    
}

mcp::json StockOrder_handler(const mcp::json& params, const std::string& /* session_id */);

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