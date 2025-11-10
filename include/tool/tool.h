#ifndef QUERY_UTIL_H
#define QUERY_UTIL_H

#include <string>
#include <map>
#include <sstream>

namespace tool {

std::string build_query(const std::map<std::string, std::string>& params) {
    std::ostringstream oss;
    bool first = true;
    for (const auto& p : params) {
        if (!first) oss << "&";
        first = false;
        oss << p.first << "=" << p.second;
    }
    return oss.str();
}

} // namespace tool

#endif // QUERY_UTIL_H