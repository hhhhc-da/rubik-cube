#include <rubik_cube_base.hpp>

// 随机数全局变量
std::random_device rd;
std::mt19937 gen(rd());
// 打乱随机数分布
std::uniform_int_distribution<nanoka_num_t> dis(0, 100);

// Map key
std::vector<nanoka_num_t> nanoka_get_keys(std::map<nanoka_num_t, nanoka_num_t> &m)
{
    std::vector<nanoka_num_t> keys;
    std::transform(m.begin(), m.end(), std::back_inserter(keys),
                   [](const std::pair<nanoka_num_t, nanoka_num_t> &pair)
                   {
                       return pair.first;
                   });
    return keys;
}

// Map value
std::vector<nanoka_num_t> nanoka_get_values(std::map<nanoka_num_t, nanoka_num_t> &m)
{
    std::vector<nanoka_num_t> values;
    std::transform(m.begin(), m.end(), std::back_inserter(values),
                   [](const std::pair<nanoka_num_t, nanoka_num_t> &pair)
                   {
                       return pair.second;
                   });
    return values;
}

nanoka_status_t nanoka_equal(std::vector<nanoka_num_t> data, nanoka_num_t value, nanoka_status_t mode)
{
    try
    {
        if (mode == NANOKA_ANY)
        {
            for (auto i : data)
                if (i == value)
                    return NANOKA_SUCCESS;
        }
        else if (mode == NANOKA_ALL)
        {
            for (auto i : data)
                if (i != value)
                    return NANOKA_ERROR;
            return NANOKA_SUCCESS;
        }
        else
            throw std::runtime_error("mode is invalid" + std::to_string(mode));
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(::nanoka_equal) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(::nanoka_equal) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

nanoka_status_t nanoka_equal(std::vector<nanoka_storage_t> data, nanoka_num_t value, nanoka_status_t mode)
{
    try
    {
        if (mode == NANOKA_ANY)
        {
            for (auto i : data)
                if (static_cast<nanoka_num_t>(i) == value)
                    return NANOKA_SUCCESS;
        }
        else if (mode == NANOKA_ALL)
        {
            for (auto i : data)
                if (static_cast<nanoka_num_t>(i) != value)
                    return NANOKA_ERROR;
            return NANOKA_SUCCESS;
        }
        else
            throw std::runtime_error("mode is invalid" + std::to_string(mode));
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(::nanoka_equal) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(::nanoka_equal) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

nanoka_status_t nanoka_equal(std::vector<nanoka_storage_t> data, std::vector<nanoka_storage_t> data2)
{
    try
    {
        if (data.size() != data2.size())
            throw std::runtime_error("compared vectors' length not fitable. data.size() = " + std::to_string(data.size()) + " data2.size() = " + std::to_string(data2.size()) + ".");

        for (nanoka_num_t i = 0; i < data.size(); ++i)
        {
            if (data.at(i) != data2.at(i))
                return NANOKA_ERROR;
        }
        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(::nanoka_equal) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(::nanoka_equal) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

nanoka_status_t nanoka_equal(std::vector<nanoka_num_t> data, std::vector<nanoka_num_t> data2)
{
    try
    {
        if (data.size() != data2.size())
            throw std::runtime_error("compared vectors' length not fitable. data.size() = " + std::to_string(data.size()) + " data2.size() = " + std::to_string(data2.size()) + ".");

        for (nanoka_num_t i = 0; i < data.size(); ++i)
        {
            if (data.at(i) != data2.at(i))
                return NANOKA_ERROR;
        }
        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(::nanoka_equal) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(::nanoka_equal) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

nanoka_status_t nanoka_in(nanoka_map_t data_map, std::vector<nanoka_storage_t> data)
{
    try
    {
        if (data_map.size() == 0)
            throw std::runtime_error("data_map.size() == 0.");

        for (nanoka_num_t i = 0; i < data_map.size(); ++i)
        {
            // 拿出我们一整层的数据；来进行遍历
            std::vector<std::vector<nanoka_storage_t>> &ly = data_map[i];

            // 如果发现相等的元素那么我们就检测到存在元素
            for (auto &elem : ly)
                if (nanoka_equal(elem, data) == NANOKA_SUCCESS)
                    return NANOKA_SUCCESS;
        }
        return NANOKA_ERROR;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(::nanoka_equal) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(::nanoka_equal) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}