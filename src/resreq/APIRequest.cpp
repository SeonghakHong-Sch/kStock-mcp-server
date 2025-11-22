#include "APIRequest.h"

namespace APIRequest {

/*baseRequest-----------------------------------------------------------*/
//생성,소멸
baseRequest::baseRequest(std::string request_id, std::string url, std::string api_name, std::string tr_id):
    request_id(request_id),
    url(url),
    api_name(api_name),
    tr_id(tr_id) {}
baseRequest::~baseRequest(){}

//변수 재설정
void baseRequest::set_tr_id(const std::string tr_id) {
    this->tr_id = tr_id;
}

void baseRequest::set_url(const std::string url) {
    this->url = url;
}


//로거용 타임스탬프
std::time_t baseRequest::getTimestamp() const {
    return timestamp;
}

//요청 URL 반환
std::string baseRequest::getURL() const {
    return url;
}


/*AccountInfoRequest-----------------------------------------------------------*/
//생성, 소멸
AccountInfoRequest::AccountInfoRequest(std::string request_id):
    baseRequest(request_id, "/uapi/domestic-stock/v1/trading/inquire-balance", "주식잔고 조회", "TTTC8434R") {}

AccountInfoRequest::~AccountInfoRequest(){};


//setRequestInfo 구현
void AccountInfoRequest::setRequestInfo(const json& request_info) {
    content_type = request_info["content-type"];
    custtype = request_info["custtype"];
    CANO = request_info["CANO"];
    ACNT_PRDT_CD = request_info["ACNT_PRDT_CD"];
    INQR_DVSN = request_info["INQR_DVSN"];
    FUND_STTL_ICLD_YN = request_info["FUND_STTL_ICLD_YN"];
    PRCS_DVSN = request_info["PRCS_DVSN"];
}


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
            {"AFHR_FLPR_YN", AFHR_FLPR_YN},
            {"OFL_YN", OFL_YN},
            {"INQR_DVSN", INQR_DVSN},
            {"UNPR_DVSN", UNPR_DVSN},
            {"FUND_STTL_ICLD_YN", FUND_STTL_ICLD_YN},
            {"FNCG_AMT_AUTO_RDPT_YN", FNCG_AMT_AUTO_RDPT_YN},
            {"PRCS_DVSN", PRCS_DVSN},
            {"CTX_AREA_FK100", CTX_AREA_FK100},
            {"CTX_AREA_NK100", CTX_AREA_NK100}
        }}
    };
}



/*StockPriceRequest-----------------------------------------------------------*/
//생성, 소멸
StockPriceRequest::StockPriceRequest(std::string request_id):
    baseRequest(request_id, "/uapi/domestic-stock/v1/quotations/inquire-price", "주식현재가 시세 조회", "FHKST01010100") {}
StockPriceRequest::~StockPriceRequest(){}

//setRequestInfo 구현
void StockPriceRequest::setRequestInfo(const json& request_info) {
    content_type = request_info["content-type"];
    custtype = request_info["custtype"];
    FID_COND_MRKT_DIV_CODE = request_info["FID_COND_MRKT_DIV_CODE"];
    FID_INPUT_ISCD = request_info["FID_INPUT_ISCD"];
}

//getRequestInfo 구현
json StockPriceRequest::getRequestInfo() {
    return {
        {"etc", {
            {"request_id", request_id},
            {"url", url},
            {"time", timestamp},
            {"api_name", api_name}
        }},
        {"headers", {
            {"content-type", content_type},
            {"tr_id", tr_id},
            {"custtype", custtype}
        }},
        {"query_params", {
            {"FID_COND_MRKT_DIV_CODE", FID_COND_MRKT_DIV_CODE},
            {"FID_INPUT_ISCD", FID_INPUT_ISCD}
        }
       }
    };
}


/*FinInfoRequest-----------------------------------------------------------*/
//생성, 소멸
FinInfoRequest::FinInfoRequest(std::string request_id):
    baseRequest(request_id, "/uapi/domestic-stock/v1/finance/financial-ratio", "재무비율 조회", "FHKST66430300") {}
FinInfoRequest::~FinInfoRequest(){}

//setRequestInfo 구현
void FinInfoRequest::setRequestInfo(const json& request_info) {
    content_type = request_info["content-type"];
    custtype = request_info["custtype"];
    FID_DIV_CLS_CODE = request_info["FID_DIV_CLS_CODE"];
    fid_cond_mrkt_div_code = request_info["fid_cond_mrkt_div_code"];
    fid_input_iscd = request_info["fid_input_iscd"];
}

//getRequestInfo 구현
json FinInfoRequest::getRequestInfo() {
    return {
        {"etc", {
            {"request_id", request_id},
            {"url", url},
            {"time", timestamp},
            {"api_name", api_name}
        }},
        {"headers", {
            {"content-type", content_type},
            {"tr_id", tr_id},
            {"custtype", custtype}
        }},
        {"query_params", {
            {"FID_DIV_CLS_CODE", FID_DIV_CLS_CODE},
            {"fid_cond_mrkt_div_code", fid_cond_mrkt_div_code},
            {"fid_input_iscd", fid_input_iscd}
        }}
    };
}


/*StockInfoRequest-----------------------------------------------------------*/
//생성, 소멸
StockInfoRequest::StockInfoRequest(std::string request_id):
    baseRequest(request_id, "/uapi/domestic-stock/v1/quotations/search-stock-info", "주식 기본조회", "CTPF1002R") {}
StockInfoRequest::~StockInfoRequest(){}

//setRequestInfo 구현
void StockInfoRequest::setRequestInfo(const json& request_info) {
    content_type = request_info["content-type"];
    custtype = request_info["custtype"];
    PDNO = request_info["PDNO"];
}

//getRequestInfo 구현
json StockInfoRequest::getRequestInfo() {
    return {
        {"etc", {
            {"request_id", request_id},
            {"url", url},
            {"time", timestamp},
            {"api_name", api_name}
        }},
        {"headers", {
            {"content-type", content_type},
            {"tr_id", tr_id},
            {"custtype", custtype}
        }},
        {"query_params", {
            {"PRDT_TYPE_CD", PRDT_TYPE_CD},
            {"PDNO", PDNO}
        }}
    };
}


/*InquireItemcharRequest-----------------------------------------------------------*/
//생성, 소멸
InquireItemcharRequest::InquireItemcharRequest(std::string request_id):
    baseRequest(request_id, "/uapi/domestic-stock/v1/quotations/inquire-daily-itemchartprice", "주식 일/주/월 시세 조회", "FHKST03010100") {}
InquireItemcharRequest::~InquireItemcharRequest(){}

//setRequestInfo 구현
void InquireItemcharRequest::setRequestInfo(const json& request_info) {
    content_type = request_info["content-type"];
    custtype = request_info["custtype"];
    FID_COND_MRKT_DIV_CODE = request_info["FID_COND_MRKT_DIV_CODE"];
    FID_INPUT_ISCD = request_info["FID_INPUT_ISCD"];
    FID_INPUT_DATE_1 = request_info["FID_INPUT_DATE_1"];
    FID_INPUT_DATE_2 = request_info["FID_INPUT_DATE_2"];
    FID_PERIOD_DIV_CODE = request_info["FID_PERIOD_DIV_CODE"];
    FID_ORG_ADJ_PRC = request_info["FID_ORG_ADJ_PRC"];
}

//getRequestInfo 구현
json InquireItemcharRequest::getRequestInfo() {
    return {
        {"etc", {
            {"request_id", request_id},
            {"url", url},
            {"time", timestamp},
            {"api_name", api_name}
        }},
        {"headers", {
            {"content-type", content_type},
            {"tr_id", tr_id},
            {"custtype", custtype}
        }},
        {"query_params", {
            {"FID_COND_MRKT_DIV_CODE", FID_COND_MRKT_DIV_CODE},
            {"FID_INPUT_ISCD", FID_INPUT_ISCD},
            {"FID_INPUT_DATE_1", FID_INPUT_DATE_1},
            {"FID_INPUT_DATE_2", FID_INPUT_DATE_2},
            {"FID_PERIOD_DIV_CODE", FID_PERIOD_DIV_CODE},
            {"FID_ORG_ADJ_PRC", FID_ORG_ADJ_PRC}
        }}
    };
}


} // namespace APIRequest