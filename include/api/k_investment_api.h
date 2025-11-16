#pragma once

#include "httplib.h"
#include "json.hpp"
#include "APIRequest.h"
#include "APIResponse.h"
#include "tool.h"

#include <string>
using json = nlohmann::json;

namespace KInvestmentAPI {

//singleton pattern 적용, 객체 하나만 생성 가능하게 ; ;
class KInvestmentAPI {

private:
    static KInvestmentAPI* instance; //
    KInvestmentAPI(); //새로운 객체 생성 금지 위해


    httplib::Client client;
    std::string base_url;
    std::string appkey, appsecret;
    std::string access_token, expires_in, access_token_token_expired;


public:
    KInvestmentAPI(const KInvestmentAPI&) = delete; //복사생성자, 대입생성자 사용 X
    KInvestmentAPI& operator=(const KInvestmentAPI&) = delete;
    ~KInvestmentAPI();

    static KInvestmentAPI* getInstance();
    static void revokeInstance();


    //단순 정보 관련
    std::string get_base_url() const;

    //연결 관련
    void setClient(json config);
    void setAccessToken();
    void revokeAccessToken();


    //request 관련
    void request_k_stock(json& request ,json& response, int method);
};


} // namespace KInvestmentAPI