#pragma once

#include "json.hpp"

#include <string>
#include <ctime>
#include <iostream>

using json = nlohmann::json;

namespace APIRequest {

class baseRequest {

protected:
    //url
    std::string url;

    //요청 api
    std::string api_name;

    //공통 요청 헤더 정보
    std::string content_type;
    std::string tr_id;
    std::string custtype;
    
    //부가정보(로깅 타임스탬프 등)
    std::time_t timestamp = std::time(nullptr);
    
    //requestid
    std::string request_id;

public:
    //생성, 소멸
    baseRequest(std::string request_id, std::string url, std::string api_name);
    ~baseRequest();

    //
    virtual void setRequestInfo(const json& request_info) = 0;
    virtual json getRequestInfo() = 0; //요청 정보만 반환(부가정보 제외)
    virtual json toJSON() = 0; //전체 요청 정보 반환(부가정보 포함)
    
    //타임스탬프 반환
    std::time_t getTimestamp() const;

    //요청 URL 반환
    std::string getURL() const;
};


class StockOrderRequest : public baseRequest {

private:

public:
    StockOrderRequest();
    ~StockOrderRequest();

};


class AccountInfoRequest : public baseRequest {

private:
    //요청 필수 파라미터
    std::string CANO;
    std::string ACNT_PRDT_CD;
    std::string INQR_DVSN;
    std::string FUND_STTL_ICLD_YN;
    std::string PRCS_DVSN;

public:
    AccountInfoRequest(std::string request_id);
    ~AccountInfoRequest();

    void setRequestInfo(const json& request_info) override;
    json getRequestInfo() override;
    json toJSON() override;


};

class StockPriceRequest : public baseRequest {


public:
    StockPriceRequest();
    ~StockPriceRequest();
};


class OrderDetailRequest : public baseRequest {


public:
    OrderDetailRequest();
    ~OrderDetailRequest();
};

} // namespace APIRequest