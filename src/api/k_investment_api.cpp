#include "k_investment_api.h"

using json = nlohmann::json;

namespace KInvestmentAPI {

    
KInvestmentAPI::KInvestmentAPI() :
    client("https://openapi.koreainvestment.com:9443"),
    base_url("https://openapi.koreainvestment.com:9443")
{

}

KInvestmentAPI::~KInvestmentAPI() {


}

std::string KInvestmentAPI::get_base_url() const {
    return base_url;
}

//한투 api 클라이언트 설정 함수
void KInvestmentAPI::setClient(json config) {
    //std::string base_url = config["base_url"];
    appkey = config["appkey"];
    appsecret = config["appsecret"];
    //std::string access_token = config["access_token"];
}

//엑세스 토큰 발급 함수
void KInvestmentAPI::setAccessToken() {
    json body = {
        {"grant_type", "client_credentials"},
        {"appkey", appkey},
        {"appsecret", appsecret}
    };
    auto res = client.Post("/oauth2/tokenP", body.dump(), "application/json"); //std::shared_ptr<httplib::Response>
    
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
    };

    auto res = client.Post("/oauth2/revokeP", body.dump(), "application/json");
    if (res && res->status == 200) {
        std::cout << "Access token revoked successfully" << std::endl;
    } else {
        std::cout << "Failed to revoke access token" << std::endl;
    }
}

void KInvestmentAPI::request_k_stock(const json& request ,json& response, int method) {

    const std::string url = request["etc"]["url"];
    const std::string api_name = request["etc"]["api_name"];
    // const httplib::Headers headers = {
    //     request["headers"].begin(), request["headers"].end(),
    //     {"authorization", access_token},
    //     {"appkey", appkey},
    //     {"appsecret", appsecret}
    // };
    httplib::Headers headers;
    for (auto& [key, value] : request["headers"].items()) {
        headers.emplace(key, value.get<std::string>());
    }
    const std::string query_params = tool::build_query(request["query_params"]);
    const std::string body = tool::build_query(request["body"]);


    switch(method) {
        case 0: {
            auto res = client.Get(url + "?" + query_params, headers);
            if (res && res->status == 200) {
                response = json::parse(res->body);
                std::cout << "GET request " + api_name + " successful" << std::endl;
            } else {
                std::cout << "GET request " + api_name + " failed" << std::endl;
            }
        }
        case 1: {
            // auto res = client.Post(url + '?' + query_params, headers, body, "application/x-www-form-urlencoded")
            // if (res && res->status == 200) {
            //     response = json::parse(res->body);
            //     std::cout << "POST request" + request["etc"]["api_name"] + " successful" << std::endl;
            // } else {
            //     std::cout << "POST request" + request["etc"]["api_name"] + " failed" << std::endl;
            // }
        }
        break;
    }


}

} //namespace KInvestmentAPI