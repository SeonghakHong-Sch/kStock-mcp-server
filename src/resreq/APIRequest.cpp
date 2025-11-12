#include "APIRequest.h"

namespace APIRequest {

/*baseRequest-----------------------------------------------------------*/
//생성,소멸
baseRequest::baseRequest(std::string request_id): request_id(request_id) {};
baseRequest::~baseRequest(){}


//로거용 타임스탬프
std::time_t baseRequest::getTimestamp() const {
    return timestamp;
};

//요청 URL 반환
std::string baseRequest::getURL() const {
    return url;
}


/*AccountInfoRequest-----------------------------------------------------------*/
//생성, 소멸
AccountInfoRequest::AccountInfoRequest(std::string request_id):
    baseRequest(request_id),
    url("/uapi/domestic-stock/v1/trading/inquire-balance")
    api_name("주식잔고 조회") {}

AccountInfoRequest::~AccountInfoRequest(){};


//setRequestInfo 구현
void AccountInfoRequest::setRequestInfo(const json& request_info) {
    content_type = request_info["content-type"];
    tr_id =  request_info["tr_id"];
    custtype = request_info["custtype"];
    CANO = request_info["CANO"];
    ACNT_PRDT_CD = request_info["ACNT_PRDT_CD"];
    INQR_DVSN = request_info["INQR_DVSN"];
    FUND_STTL_ICLD_YN = request_info["FUND_STTL_ICLD_YN"];
    PRCS_DVSN = request_info["PRCS_DVSN"];
};


//getRequestInfo 구현
json AccountInfoRequest::getRequestInfo() {
    return {
        {
            "etc", {
                {"request_id", request_id},
                {"url", url},
                {"time", timestamp},
                {"api_name", api_name}
            }
        },
        {"headers", {
            {"content-type", content_type},
            {"tr_id", tr_id},
            {"custtype", custtype}
        }},
        {"query_params", {
            {"CANO", CANO},
            {"ACNT_PRDT_CD", ACNT_PRDT_CD},
            {"INQR_DVSN", INQR_DVSN},
            {"FUND_STTL_ICLD_YN", FUND_STTL_ICLD_YN},
            {"PRCS_DVSN", PRCS_DVSN}
        }}
    };
};


//toJSON 구현
json AccountInfoRequest::toJSON() {
    return {
        {"request_id", request_id},
        {"url", url},
        {"time", timestamp},
        {"content-type", content_type},
        {"tr_id", tr_id},
        {"custtype", custtype},
        {"CANO", CANO},
        {"ACNT_PRDT_CD", ACNT_PRDT_CD},
        {"INQR_DVSN", INQR_DVSN},
        {"FUND_STTL_ICLD_YN", FUND_STTL_ICLD_YN},
        {"PRCS_DVSN", PRCS_DVSN}
    };
};


} // namespace APIRequest