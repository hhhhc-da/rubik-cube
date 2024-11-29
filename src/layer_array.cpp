#include <layer_array.hpp>

// 旋转九十度函数 (默认顺时针, 开启 reverse 可以逆时针旋转 90 度)
nanoka_status_t Layer_Array::route_90(bool reverse = false)
{
    // 拷贝一份后构造
    try
    {
        nanoka_num_t a = sqrt(data_len);
        if (a * a != data_len)
            throw std::runtime_error("data_len cannot be divided.");

        if (reverse)
        {
            for (nanoka_num_t i = 0; i < a - 1; ++i)
            {
                nanoka_storage_t data = storage.at(0);
                storage.emplace(storage.begin() + storage.size() - 1, data);
                storage.erase(storage.begin(), storage.begin() + 1);
            }
            return NANOKA_SUCCESS;
        }
        else
        {
            for (nanoka_num_t i = 0; i < a - 1; ++i)
            {
                nanoka_storage_t data = storage.at(data_len - 2);
                storage.emplace(storage.begin(), data);
                storage.erase(storage.begin() + storage.size() - 2, storage.begin() + storage.size() - 1);
            }
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

// 将数据拷贝进去
Layer_Array &Layer_Array::operator=(std::vector<nanoka_storage_t> data)
{
    if (data.size() != data_len)
        throw std::runtime_error("(Layer_Array::operator=) vector size not fitable.");

    storage = data;
    return *this;
}

// 获取当前的面结果 (不允许外部修改)
std::vector<nanoka_storage_t> Layer_Array::get_storage(void) const
{
    return storage;
}

void Layer_Array::print_storage(void) const
{
    try
    {
        nanoka_num_t a = sqrt(data_len);
        if (a * a != data_len)
            throw std::runtime_error("data_len cannot be divided.");

        std::vector<nanoka_num_t> cube_layer = {0, 1, 2, 7, 8, 3, 6, 5, 4};

        // 三阶魔方输出顺序
        std::cout << "Print storage:" << std::endl;
        // 顺序存储的时候使用的输出函数
        for (nanoka_num_t i = 0; i < a; ++i)
        {
            std::cout << "|" << std::flush;
            for (nanoka_num_t j = 0; j < a; ++j)
            {
                std::cout << " "
                          << static_cast<nanoka_num_t>(storage.at(cube_layer[a * i + j]));
            }
            std::cout << " |\n";
        }
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Layer_Array::print_storage) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Layer_Array::print_storage) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
}

// 读取我感兴趣的部分
std::vector<nanoka_storage_t> Layer_Array::read(nanoka_num_t pos)
{
    std::vector<nanoka_storage_t> ret;
    try
    {
        if (storage.size() != data_len)
            throw std::runtime_error("storage.size() != data_len.");

        nanoka_num_t a = sqrt(data_len);
        if (a * a != data_len)
            throw std::runtime_error("data_len cannot be divided.");

        // 修改顺序 <8,9,4>,<2,9,6>
        std::map<nanoka_num_t, std::vector<nanoka_num_t>> m = {
            {0, {0, 1, 2}}, {1, {2, 3, 4}}, {2, {4, 5, 6}}, {3, {6, 7, 0}}, {4, {7, 8, 3}}, {5, {1, 8, 5}}};

        // 修改顺序 <1,2,3>,<3,4,5>,<5,6,7>,<7,8,1>,<8,9,4>,<2,9,6>
        for (nanoka_num_t i = 0; i < a; ++i)
            ret.emplace_back(storage.at(m[pos].at(i)));
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Layer_Array::print_storage) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Layer_Array::print_storage) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return ret;
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

// 测试旋转用顺序填充区块函数
nanoka_status_t Layer_Array::valid(nanoka_num_t start_color)
{
    try
    {
        if (data_len <= 0 || storage.size() == 0)
            throw std::runtime_error("Vector storage is empty!");

        for (nanoka_num_t i = 0; i < data_len; ++i)
            storage.at(i) = start_color + i;

        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Layer_Array::valid) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Layer_Array::valid) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
    }
    return NANOKA_ERROR;
}

// 修改 vector 区块
nanoka_status_t Layer_Array::alter(nanoka_num_t pos, std::vector<nanoka_storage_t> data)
{
    try
    {
        nanoka_num_t a = sqrt(data_len);
        if (a * a != data_len)
            throw std::runtime_error("data_len cannot be divided.");

        if (data.size() < a)
            throw std::runtime_error("(Layer_Array::alter) Vector size is too small!");

        // 修改顺序 <8,9,4>,<2,9,6>
        std::map<nanoka_num_t, std::vector<nanoka_num_t>> m = {
            {0, {0, 1, 2}}, {1, {2, 3, 4}}, {2, {4, 5, 6}}, {3, {6, 7, 0}}, {4, {7, 8, 3}}, {5, {1, 8, 5}}};

        for (nanoka_num_t i = 0; i < a; ++i)
            storage.at(m[pos].at(i)) = data.at(i);

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
