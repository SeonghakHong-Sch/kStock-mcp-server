#include "k_investment_api.h"

using namespace json = nlohmann::json;

namespace KInvestmentAPI {

    
KInvestmentAPI::KInvestmentAPI() {

}

KInvestmentAPI::~KInvestmentAPI() {


}

std::string KInvestmentAPI::get_base_url() const {
    return base_url;
}

void KInvestmentAPI::setClient(json config) {
    std::string base_url = config["base_url"];
    appkey = config["appkey"];
    appsecret = config["appsecret"];
    //std::string access_token = config["access_token"];
    client = httplib::Client(base_url);
}

void KInvestmentAPI::setAccessToken() {
    json body = {
        {"grant_type", "client_credentials"},
        {"appkey", appkey},
        {"appsecret", appsecret}
    };
    auto res = client.Post("/oauth2/tokenP", body.dump(), "application/json");
    if (res && res->status == 200) {
        json response_json = json::parse(res->body);
        access_token = response_json["access_token"];
        expires_in = response_json["expires_in"];
        access_token_token_expired = response_json["access_token_token_expired"];

        //일단은 예외처리 요렇게
        std::cout << "Access token set successfully: " << access_token << std::endl;
    } else {
        std::cout << "Failed to obtain access token" << std::endl;
    }
}

void KInvestmentAPI::revokeAccessToken() {
    json body = {
        {"appkey", std::getenv("K_appkey")},
        {"appsecret", std::getenv("K_appsecret")},
        {"token", access_token}
    }

    auto res = client.Post("/oauth2/revokeP", body.dump(), "application/json");
    if (res && res->status == 200) {
        std::cout << "Access token revoked successfully" << std::endl;
    } else {
        std::cout << "Failed to revoke access token" << std::endl;
    }
}


APIResponse::StockOrderResponse KInvestmentAPI::requestStockOrder(const APIRequest::StockOrderRequest& request) {
    APIResponse::StockOrderResponse response;

    // 기달

    return response;
}

APIResponse::AccountInfoResponse KInvestmentAPI::requestAccountInfo(const APIRequest::AccountInfoRequest& request) {
    httplib::Headers headers = {
        {"authorization", "Bearer " + access_token},
        {"appkey", appkey},
        {"appsecret", appsecret},
        {"tr_id", "TTTC8434R"} //계좌정보조회 tr_id
    };


    std::map<std::string, std::string> params = {
        {"CANO", request.getCANO()},
        {"ACNT_PRDT_CD", request.getACNT_PRDT_CD()},
        {"INQR_DVSN", request.getINQR_DVSN()},
        {"FUND_STTL_ICLD_YN", "N"},
        {"PRCS_DVSN", "00"}
    };
    std::string query = tool::build_query(params);
    
    auto res = client.Get(("/uapi/domestic-stock/v1/trading/inquire-balance" + query).c_str(), headers);
    
    APIResponse::AccountInfoResponse response;

    // 기달

    return response;


} //namespace KInvestmentAPI