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


/*StockPriceResponse-----------------------------------------------------------*/
StockPriceResponse::StockPriceResponse(std::string request_id):
    baseResponse(request_id) {}
StockPriceResponse::~StockPriceResponse() {}


void StockPriceResponse::setResponseInfo(const json& response_info) {
    msg_cd = response_info["msg_cd"];
    msg1 = response_info["msg1"];
    data_obj = response_info["output"];
}


json StockPriceResponse::getResponseInfo() {
    return {
        "etc", {
            {"request_id", request_id},
            {"time", timestamp},
        },
        "data", data_obj
    };
}


/*FinInfoResponse-----------------------------------------------------------*/
FinInfoResponse::FinInfoResponse(std::string request_id):
    baseResponse(request_id) {}
FinInfoResponse::~FinInfoResponse() {}


void FinInfoResponse::setResponseInfo(const json& response_info) {
    //msg_cd = response_info["msg_cd"];
    //msg1 = response_info["msg1"];
    fin_ratio_list = response_info["fin_ratio_list"]["output"];
    fin_income_list = response_info["fin_income_list"]["output"];
    fin_balance_list = response_info["fin_balance_list"]["output"];
}


json FinInfoResponse::getResponseInfo() {
    return {
        "etc", {
            {"request_id", request_id},
            {"time", timestamp},
        },
        "data", {
            {"fin_ratio_list", fin_ratio_list},
            {"fin_income_list", fin_income_list},
            {"fin_balance_list", fin_balance_list}
        }
    };
}


/*StockInfoResponse-----------------------------------------------------------*/
StockInfoResponse::StockInfoResponse(std::string request_id):
    baseResponse(request_id) {}
StockInfoResponse::~StockInfoResponse() {}


void StockInfoResponse::setResponseInfo(const json& response_info) {
    msg_cd = response_info["msg_cd"];
    msg1 = response_info["msg1"];
    data_obj = response_info["output"];
}


json StockInfoResponse::getResponseInfo() {
    return {
        "etc", {
            {"request_id", request_id},
            {"time", timestamp},
        },
        "data", data_obj
    };
}


/*InquireItemcharResponse-----------------------------------------------------------*/
InquireItemcharResponse::InquireItemcharResponse(std::string request_id):
    baseResponse(request_id) {}
InquireItemcharResponse::~InquireItemcharResponse() {}


void InquireItemcharResponse::setResponseInfo(const json& response_info) {
    msg_cd = response_info["msg_cd"];
    msg1 = response_info["msg1"];
    data_obj = response_info["output"];
}


json InquireItemcharResponse::getResponseInfo() {
    return {
        "etc", {
            {"request_id", request_id},
            {"time", timestamp},
        },
        "data", data_obj
    };
}



} // namespace APIResponse