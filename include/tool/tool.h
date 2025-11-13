#pragma once

#include "json.hpp"

#include <string>
#include <map>
#include <sstream>

namespace tool {

inline std::string build_query(const json& params) {
    std::ostringstream oss;
    bool first = true;

    for (auto it = params.begin(); it != params.end(); ++it) {
        if (!first) oss << "&";
        first = false;

        oss << it.key() << "=";

        //문자열이면 따옴표 제거, 아니면 그대로 문자열화
        const auto& value = it.value();
        if (value.is_string()) {
            oss << value.get<std::string>();
        } else {
            oss << value.dump();  // 숫자/불린 등을 문자열로 변환
        }
    }

    return oss.str();
}

inline bool check_json(const json& params, const std::vector<std::string>& required_keys) {
    for(const auto& key : required_keys) {
        if(!params.contains(key)) {
            return false;
        }
    }
    return true;
}

} // namespace tool
