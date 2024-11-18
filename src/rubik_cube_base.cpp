#include <rubik_cube_base.hpp>

// 获取 Map 的主键
std::vector<nanoka_num_t> nanoka_get_keys(std::map<nanoka_num_t, nanoka_num_t>& m)
{
    std::vector<nanoka_num_t> keys;
    std::transform(m.begin(), m.end(), std::back_inserter(keys),
                   [](const std::pair<nanoka_num_t, nanoka_num_t>& pair)
                   {
                       return pair.first;
                   });
    return keys;
}

// 获取 Map 的值
std::vector<nanoka_num_t> nanoka_get_values(std::map<nanoka_num_t, nanoka_num_t>& m)
{
    std::vector<nanoka_num_t> values;
    std::transform(m.begin(), m.end(), std::back_inserter(values),
                   [](const std::pair<nanoka_num_t, nanoka_num_t>& pair)
                   {
                       return pair.second;
                   });
    return values;
}