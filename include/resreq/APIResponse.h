#include "json.hpp"

#include <string>
#include <ctime>
#include <iostream>
#include <vector>

using json = nlohmann::json;

namespace APIResponse {

class baseResponse {

protected:
    std::string content_type;
    std::string rt_cd; //성공 실패 여부, 0이면 성공
    std::string msg_cd; //응답 코드
    std::string msg1; //메세지 응답내용

    //부가정보
    std::time_t timestamp = std::time(nullptr);

public:
    //생성, 소멸
    baseResponse();
    ~baseResponse();

    //
    virtual void setResponseInfo(const json& response_info) = 0;
    virtual json getResponseInfo() = 0; //응답 정보만 반환(부가정보 제외)
    virtual json toJSON() = 0; //전체 응답 정보 반환(부가정보 포함)

    //응답 성공 여부 반환
    bool isValidResponse();

    //타임스탬프 반환
    std::time_t getTimestamp() const;
}

class AccountInfoResponse : public baseResponse {

private:
    std::vector<json> account_list; // 계좌 주식 정보 리스트
    std::vector<json> balance_list; // 계좌 잔고 정보 리스트

public:
    AccountInfoResponse();
    ~AccountInfoResponse();

    void setResponseInfo(const json& response_info) override;
    json getResponseInfo() override;
    json toJSON() override;
    

}


} // namespace APIResponse