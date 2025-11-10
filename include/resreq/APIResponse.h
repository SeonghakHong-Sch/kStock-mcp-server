#include "json.hpp"

#include <string>
#include <json.hpp>
#include <ctime>
#include <iostream>
#include <vector>

using json = nlohmann::json;

namespace APIResponse {

class APIResponse {

protected:
    std::string content_type;
    std::string rt_cd; //성공 실패 여부
    std::string msg_cd; //메세지 코드
    std::string msg1; //메세지 응답내용

    //부가정보
    time_t timestamp;

public:
    //생성, 소멸
    APIResponse();
    ~APIResponse();

    void isValidResponse();
}

class AccountInfoResponse : public APIResponse {

private:
    std::vector<json> account_list; // 계좌 주식 정보 리스트
    std::vector<json> balance_list; // 계좌 잔고 정보 리스트

public:
    AccountInfoResponse();
    ~AccountInfoResponse();

    //정보 추출
    const std::vector<json>& getAccountList() const;
    const std::vector<json>& getBalanceList() const;

    //응답 파싱 후 객체에 저장
    bool parseFromJson(const json& response);

    //기타 오퍼레이션
    int getHoldingStockCount() const;
    

}


} // namespace APIRequest