#include <string>
#include <json.hpp>

using json = nlohmann::json;

namespace APIRequest {

class baseAPIRequest {

private:

public:
    baseAPIRequest();
    ~baseAPIRequest();

}


class StockOrderRequest : public baseAPIRequest {

private:

public:
    StockOrderRequest();
    ~StockOrderRequest();

} 


class AccountInfoRequest : public baseAPIRequest {

public:
    AccountInfoRequest();
    ~AccountInfoRequest();
}

class StockPriceRequest : public baseAPIRequest {


public:
    StockPriceRequest();
    ~StockPriceRequest();
}


class OrderDetailRequest : public baseAPIRequest {


public:
    OrderDetailRequest();
    ~OrderDetailRequest();
}

} // namespace APIRequest