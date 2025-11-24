#include "k_investment_api.h"
#include <typeinfo>
using json = nlohmann::json;

namespace KInvestmentAPI {

//기본생성자;    
KInvestmentAPI::KInvestmentAPI() :
    client("https://openapi.koreainvestment.com:9443"),
    base_url("https://openapi.koreainvestment.com:9443") {}

KInvestmentAPI::~KInvestmentAPI() {}


//singleton pattern
KInvestmentAPI* KInvestmentAPI::instance = nullptr; //가독성 꼬라지 ㅅㅂ...

//instance 생성 및 return
KInvestmentAPI* KInvestmentAPI::getInstance() {
    if (instance == nullptr) {
        instance = new KInvestmentAPI();
    }
    return instance;
}

//인스턴스 할당 해제
void KInvestmentAPI::revokeInstance() {
    if (instance != nullptr) {
        delete instance;
    }
    instance = nullptr;
    return;
}


//baseurl 뽑기
std::string KInvestmentAPI::get_base_url() const {
    return base_url;
}

//토큰 연결 여부 확인
bool KInvestmentAPI::isConnected() const {
    return !access_token.empty();
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
        access_token = "Bearer " + response_json["access_token"].get<std::string>();
        expires_in = response_json["expires_in"].dump(); //to string
        access_token_token_expired = response_json["access_token_token_expired"];

        LOG_INFO("Access token set successfully");
    } else {
        LOG_ERROR("Failed to set access token");
        throw std::runtime_error("Failed to obtain access token");
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
        LOG_INFO("Access token revoked successfully");
    } else {
        LOG_ERROR("Failed to revoke access token");
        throw std::runtime_error("Failed to revoke access token");
    }
}

void KInvestmentAPI::request_k_stock(json& request ,json& response, int method) {

    const std::string url = request["etc"]["url"];
    const std::string api_name = request["etc"]["api_name"];
    // const httplib::Headers headers = {
    //     request["headers"].begin(), request["headers"].end(),
    //     {"authorization", access_token},
    //     {"appkey", appkey},
    //     {"appsecret", appsecret}
    // };
    request["headers"]["authorization"] = access_token;
    request["headers"]["appkey"] = appkey;
    request["headers"]["appsecret"] = appsecret;
    httplib::Headers headers;
    for (auto& [key, value] : request["headers"].items()) {
        headers.emplace(key, value.get<std::string>());
    }
    
    switch(method) {
        case 0: { //GET
            const std::string query_params = tool::build_query(request["query_params"]);
            auto res = client.Get(url + "?" + query_params, headers);
            
            if (!res || res->status != 200) {
                LOG_ERROR(api_name, "API Request failed");
                throw std::runtime_error("API Request failed");
            }

            response = json::parse(res->body);

            if (response["rt_cd"] == "0") {
                LOG_INFO("Get request ", api_name, ": successful");
            } else {
                LOG_ERROR("Get request ", api_name, ": failed", response.dump(2));
                throw std::runtime_error("K-stock investment API response is invalid");
            }

            break;
        }

        case 1: { //POST
            //const std::string body = tool::build_query(request["body"]);

            const httplib::Params params = {
                request["body"].begin(), request["body"].end()
            };
            auto res = client.Post(url, headers, params);

            if (!res || res->status != 200) {
                LOG_ERROR(api_name, "API Request failed");
                throw std::runtime_error("API Request failed");
            }

            response = json::parse(res->body);
            
            if (response["rt_cd"] == "0") {
                LOG_INFO("Get request ", api_name, ": successful");
            } else {
                LOG_ERROR("Get request ", api_name, ": failed", response.dump(2));
                throw std::runtime_error("K-stock investment API response is invalid");
            }

            break;
        }

        default:
            throw std::runtime_error("Invalid API method");
    }


}

} //namespace KInvestmentAPI