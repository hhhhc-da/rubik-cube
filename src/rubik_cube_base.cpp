#include <rubik_cube_base.hpp>

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

nanoka_status_t nanoka_equal(std::vector<nanoka_storage_t> data, std::vector<nanoka_storage_t> data2)
{
    try
    {
        if (data.size() != data2.size())
            throw std::runtime_error("compared vectors' length not fitable.");

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
            throw std::runtime_error("compared vectors' length not fitable.");

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