#include "APIResponse.h"

namespace APIResponse {

/*baseResponse-----------------------------------------------------------*/
//생성, 소멸
baseResponse::baseResponse(){};
baseResponse::~baseResponse(){};

//응답 성공 여부 반환
bool baseResponse::isValidResponse() {
    return rt_cd == "0";
}

//타임스탬프 반환
std::time_t baseResponse::getTimestamp() const {
    return timestamp;
}


/*AccountInfoResponse-----------------------------------------------------------*/
void AccountInfoResponse::setResponseInfo(const json& response_info) {
    content_type = response_info["content-type"];
    rt_cd = response_info["rt_cd"];
    msg_cd = response_info["msg_cd"];
    msg1 = response_info["msg1"];
    //account_list = response_info["account_list"];
    //balance_list = response_info["balance_list"];
    //추후 구현
}

json AccountInfoResponse::getResponseInfo() {
    return {
        {"account_list", account_list},
        {"balance_list", balance_list}
    };
}

json AccountInfoResponse::toJSON() {
    return {
        {"content-type", content_type},
        {"rt_cd", rt_cd},
        {"msg_cd", msg_cd},
        {"msg1", msg1},
        {"account_list", account_list},
        {"balance_list", balance_list},
        {"timestamp", timestamp}
    };
}



} // namespace APIResponse