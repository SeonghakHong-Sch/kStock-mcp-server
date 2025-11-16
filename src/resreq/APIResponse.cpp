#include "APIResponse.h"

namespace APIResponse {

/*baseResponse-----------------------------------------------------------*/
//생성, 소멸
baseResponse::baseResponse(std::string request_id):
    request_id(request_id) {}
baseResponse::~baseResponse(){}


//타임스탬프 반환
std::time_t baseResponse::getTimestamp() const {
    return timestamp;
}


/*AccountInfoResponse-----------------------------------------------------------*/
AccountInfoResponse::AccountInfoResponse(std::string request_id):
    baseResponse(request_id) {}
AccountInfoResponse::~AccountInfoResponse() {}

void AccountInfoResponse::setResponseInfo(const json& response_info) {
    msg_cd = response_info["msg_cd"];
    msg1 = response_info["msg1"];
    s_balance_list = response_info["output1"];
    a_balance_list = response_info["output2"];
}

json AccountInfoResponse::getResponseInfo() {
    return {
        "etc", {
            {"request_id", request_id},
            {"time", timestamp},
        },
        "data", {
            {"s_balance_list", s_balance_list},
            {"a_balance_list", a_balance_list}
        }
    };
}




} // namespace APIResponse