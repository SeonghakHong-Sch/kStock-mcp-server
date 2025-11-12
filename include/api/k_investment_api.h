#include "httplib.h"
#include "json.hpp"
#include "APIRequest.h"
#include "APIResponse.h"
#include "tool.h"

#include <string>
using json = nlohmann::json;

namespace KInvestmentAPI {

class KInvestmentAPI {

private:
    httplib::Client client;
    std::string base_url;
    std::string appkey, appsecret;
    std::string access_token, expires_in, access_token_token_expired;


public:
    KInvestmentAPI();
    ~KInvestmentAPI();

    std::string get_base_url() const;

    //연결 관련
    void setClient(json config);
    void setAccessToken();
    void revokeAccessToken();


    //request 관련
    void request_k_stock(const json& request ,json& response, std::string method);
};


} // namespace KInvestmentAPI