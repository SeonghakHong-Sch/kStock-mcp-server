#pragma once

#include "json.hpp"

#include <string>
#include <ctime>
#include <iostream>

using json = nlohmann::json;

namespace APIRequest {

//기본
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
    baseRequest(std::string request_id, std::string url, std::string api_name, std::string tr_id);
    ~baseRequest();

    //
    virtual void setRequestInfo(const json& request_info) = 0;
    virtual json getRequestInfo() = 0; //요청객체 모든정보 json 반환
    
    //타임스탬프 반환
    std::time_t getTimestamp() const;

    //요청 URL 반환
    std::string getURL() const;
};


//주식주문(현금) 요청 class
class StockOrderRequest : public baseRequest {

private:

public:
    StockOrderRequest();
    ~StockOrderRequest();

};


//주식잔고조회 요청 class
class AccountInfoRequest : public baseRequest {

private:
    //요청 필수 파라미터
    std::string CANO; //한투 계좌번호 앞 8자리
    std::string ACNT_PRDT_CD; //계좌 끝 2자리
    std::string AFHR_FLPR_YN = "N";
    std::string OFL_YN = "";
    std::string INQR_DVSN;
    std::string UNPR_DVSN = "01";
    std::string FUND_STTL_ICLD_YN;
    std::string FNCG_AMT_AUTO_RDPT_YN = "N";
    std::string PRCS_DVSN;
    std::string CTX_AREA_FK100 = "";
    std::string CTX_AREA_NK100 = "";

public:
    AccountInfoRequest(std::string request_id);
    ~AccountInfoRequest();

    void setRequestInfo(const json& request_info) override;
    json getRequestInfo() override;

};


//주식현재가 시세 조회 요청 class
class StockPriceRequest : public baseRequest {

private:
    std::string FID_COND_MRKT_DIV_CODE = "J"; //시장 분류 코드 (J:KRX,)
    std::string FID_INPUT_ISCD; //종목 코드(005930 삼전 등)

public:
    StockPriceRequest(std::string request_id);
    ~StockPriceRequest();

    void setRequestInfo(const json& request_info) override;
    json getRequestInfo() override;

};


class OrderDetailRequest : public baseRequest {


public:
    OrderDetailRequest();
    ~OrderDetailRequest();
};

} // namespace APIRequest