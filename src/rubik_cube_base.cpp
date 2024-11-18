#include <rubik_cube_base.hpp>

// Map key
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

// Map value
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