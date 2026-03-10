#include "helpers.hpp"
#include <vector>


std::vector<Area> concatenate(const std::vector<Area>& v1, const std::vector<Area>& v2) {
    std::vector<Area> result;
    result.reserve(v1.size() + v2.size());
    result.insert(result.end(), v1.begin(), v1.end());
    result.insert(result.end(), v2.begin(), v2.end());
    return result;
}