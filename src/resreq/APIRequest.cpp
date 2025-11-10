#include "APIRequest.h"

namespace APIRequest {

/*baseAPIRequest-----------------------------------------------------------*/
//생성,소멸
baseAPIRequest::baseAPIRequest(std::string request_id){
    this->request_id = request_id;
};
baseAPIRequest::~baseAPIRequest(){};


void setTimestamp() {
    timestamp = std::time(nullptr);
};

//로거용 타임스탬프
std::time_t baseAPIRequest::getTimestamp() const {
    return timestamp;
};


/*baseAPIRequest-----------------------------------------------------------*/
//생성, 소멸
AccountInfoRequest::AccountInfoRequest(std::string request_id): baseAPIRequest(request_id) {};
AccountInfoRequest::~AccountInfoRequest(){};


//setRequestInfo 구현
void AccountInfoRequest::setRequestInfo(const json& request_info) {
    timestamp = std::time(nullptr);
    content_type = request_info["content-type"];
    tr_id =  request_info["tr_id"];
    custtype = request_info["custtype"];
    CANO = request_info["CANO"];
    ACNT_PRDT_CD = request_info["ACNT_PRDT_CD"];
    INQR_DVSN = request_info["INQR_DVSN"];
    FUND_STTL_ICLD_YN = request_info["FUND_STTL_ICLD_YN"];
    PRCS_DVSN = request_info["PRCS_DVSN"];
};


//메소드 구현
json AccountInfoRequest::getRequestInfo() {
    result = {
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