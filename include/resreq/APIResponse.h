#pragma once

#include "json.hpp"

#include <string>
#include <ctime>
#include <iostream>
#include <vector>

using json = nlohmann::json;

namespace APIResponse {

class baseResponse {

protected:
    std::string request_id;
    std::string msg_cd; //응답 코드
    std::string msg1; //메세지 응답내용

    //부가정보
    std::time_t timestamp = std::time(nullptr);

public:
    //생성, 소멸
    baseResponse(std::string request_id);
    ~baseResponse();

    //
    virtual void setResponseInfo(const json& response_info) = 0;
    virtual json getResponseInfo() = 0; //응답 정보 반환

    //타임스탬프 반환
    std::time_t getTimestamp() const;
};


//주식 계좌정보 response class
class AccountInfoResponse : public baseResponse {

private:
    std::vector<json> s_balance_list; // 계좌 주식 정보 리스트
    std::vector<json> a_balance_list; // 계좌 잔고 정보 리스트

public:
    AccountInfoResponse(std::string request_id);
    ~AccountInfoResponse();

    void setResponseInfo(const json& response_info) override;
    json getResponseInfo() override;
    

};


//주식 현재가 정보 response class
class StockPriceResponse : public baseResponse {

private:
    json data_obj;

public:
    StockPriceResponse(std::string request_id);
    ~StockPriceResponse();

    void setResponseInfo(const json& response_info) override;
    json getResponseInfo() override;

};


//재무비율  response class
class FinRatioResponse : public baseResponse {

private:
    json data_obj;

public: 
    FinRatioResponse(std::string request_id);
    ~FinRatioResponse();

    void setResponseInfo(const json& response_info) override;
    json getResponseInfo() override;
};

} // namespace APIResponse