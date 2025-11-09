#include "httplib.h"
#include <string>
#include "json.hpp"

namespace KInvestmentAPI {

class KInvestmentAPI {

private:
    httplib::Client* client;
    std::string url;
    std::string grantType, appKey, app_secret;


public:
    KInvestmentAPI();
    ~KInvestmentAPI();
    void setClient();

}


} // namespace KInvestmentAPI