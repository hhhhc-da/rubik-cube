#include <layer_array.hpp>

// 旋转九十度函数 (默认顺时针, 开启 reverse 可以逆时针旋转 90 度)
nanoka_status_t Layer_Array::route_90(bool reverse = false)
{
    // 拷贝一份后构造
    try
    {
        if (!reverse)
        {
            nanoka_storage_t data = storage.at(0);
            storage.emplace_back(data);
            return NANOKA_SUCCESS;
        }
        else
        {
            nanoka_storage_t data = storage.at(data_len - 1);
            storage.emplace(storage.begin(), data);
            return NANOKA_SUCCESS;
        }
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Layer_Array::route_90) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Layer_Array::route_90) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

// 获取当前的面结果 (不允许外部修改)
std::vector<nanoka_storage_t> Layer_Array::get_storage(void) const
{
    return storage;
}

// 获取所有旋转后的情况结果
std::set<std::vector<nanoka_storage_t>> Layer_Array::get_all_route_case(void)
{
    std::set<std::vector<nanoka_storage_t>> all_case;
    // 深拷贝
    std::vector temp_cube = storage;

    for (nanoka_num_t i = 0; i < data_len; ++i)
    {
        std::vector<nanoka_storage_t> pack = temp_cube;
        all_case.insert(pack);

        nanoka_storage_t data = temp_cube.at(0);
        temp_cube.emplace_back(data);
    }

    return all_case;
}

// 填充四个区块
nanoka_status_t Layer_Array::full(nanoka_num_t color)
{
    try
    {
        if (data_len <= 0 || storage.size() == 0)
            throw std::runtime_error("Vector storage is empty!");

        for (nanoka_num_t i = 0; i < data_len; ++i)
            storage.at(i) = color;
        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Layer_Array::full) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Layer_Array::full) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

// 修改两个区块(0,1,2,3 分别表示修改 <1,2>,<2,4>,<4,3>,<3,1>)
nanoka_status_t Layer_Array::alter(nanoka_num_t pos, nanoka_num_t data)
{
    try
    {
        storage.at(pos % data_len) = data;
        storage.at((pos + 1) % data_len) = data;
        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Layer_Array::alter) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Layer_Array::alter) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

// 修改两个区块(0,1,2,3 分别表示修改 <1,2>,<2,4>,<4,3>,<3,1>)
nanoka_status_t Layer_Array::alter(nanoka_num_t pos, nanoka_num_t data1, nanoka_num_t data2)
{
    try
    {
        storage.at(pos % data_len) = data1;
        storage.at((pos + 1) % data_len) = data2;
        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Layer_Array::alter) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Layer_Array::alter) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

// 修改两个区块(0,1,2,3 分别表示修改 <1,2>,<2,4>,<4,3>,<3,1>)
nanoka_status_t Layer_Array::alter(nanoka_num_t pos, std::vector<nanoka_num_t> data)
{
    try
    {
        if (data.size() < 2)
        {
            throw std::runtime_error("(Layer_Array::alter) Vector size is too small!");
        }
        storage.at(pos % data_len) = data.at(0);
        storage.at((pos + 1) % data_len) = data.at(1);
        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Layer_Array::alter) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Layer_Array::alter) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

// 修改两个区块(0,1,2,3 分别表示修改 <1,2>,<2,4>,<4,3>,<3,1>)
nanoka_status_t Layer_Array::alter(nanoka_num_t pos, std::pair<nanoka_num_t, nanoka_num_t> data)
{
    try
    {
        storage.at(pos % data_len) = data.first;
        storage.at((pos + 1) % data_len) = data.second;
        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Layer_Array::alter) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Layer_Array::alter) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}
