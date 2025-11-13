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
        oss << it.key() << "=" << it.value().get<std::string>();
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
