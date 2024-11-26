#include <layer_array.hpp>

// ��ת��ʮ�Ⱥ��� (Ĭ��˳ʱ��, ���� reverse ������ʱ����ת 90 ��)
nanoka_status_t Layer_Array::route_90(bool reverse = false)
{
    // ����һ�ݺ���
    try
    {
        if (reverse)
        {
            nanoka_storage_t data = storage.at(0);
            storage.emplace_back(data);
            storage.erase(storage.begin(), storage.begin() + 1);
            return NANOKA_SUCCESS;
        }
        else
        {
            nanoka_storage_t data = storage.at(data_len - 1);
            storage.emplace(storage.begin(), data);
            storage.pop_back();
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

// ��ȡ��ǰ������ (�������ⲿ�޸�)
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

        std::cout << "Print storage:" << std::endl;
        // // ˳��洢��ʱ��ʹ�õ��������
        // for (nanoka_num_t i = 0; i < a; ++i)
        // {
        //     std::cout << "|" << std::flush;
        //     for (nanoka_num_t j = 0; j < a; ++j)
        //     {
        //         std::cout << " "
        //                   << static_cast<nanoka_num_t>(storage.at(a * i + j));
        //     }
        //     std::cout << " |\n";
        // }

        // ˳ʱ��洢ʱʹ�õ����⺯�� (���޶���ħ��ʹ��)
        std::cout << "| " << static_cast<nanoka_num_t>(storage.at(0))
                  << " " << static_cast<nanoka_num_t>(storage.at(1)) << " |\n"
                  << "| " << static_cast<nanoka_num_t>(storage.at(3))
                  << " " << static_cast<nanoka_num_t>(storage.at(2)) << " |\n"
                  << std::flush;
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

// ��ȡ�Ҹ���Ȥ�Ĳ���
std::vector<nanoka_storage_t> Layer_Array::read(nanoka_num_t pos){
    std::vector<nanoka_storage_t> ret;

    try
    {
        if (storage.size() != data_len)
            throw std::runtime_error("storage.size() != data_len.");

        // �޸�˳�� <1,2>,<2,4>,<4,3>,<3,1>
        switch(pos){
            case 0:
                ret.push_back(storage.at(0));
                ret.push_back(storage.at(1));
                break;
            case 1:
                ret.push_back(storage.at(1));
                ret.push_back(storage.at(3));
                break;
            case 2:
                ret.push_back(storage.at(3));
                ret.push_back(storage.at(2));
                break;
            case 3:
                ret.push_back(storage.at(2));
                ret.push_back(storage.at(0));
                break;
            default:
                throw std::runtime_error("(out of range) read pos invalid.");
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
    return ret;
}

// ��ȡ������ת���������
nanoka_case_t Layer_Array::get_all_route_case(void)
{
    std::set<std::vector<nanoka_storage_t>> all_case;
    // ���
    std::vector<nanoka_storage_t> temp_cube = storage;

    for (nanoka_num_t i = 0; i < data_len; ++i)
    {
        std::vector<nanoka_storage_t> pack = temp_cube;
        all_case.insert(pack);

        nanoka_storage_t data = temp_cube.at(0);
        temp_cube.emplace_back(data);
        temp_cube.erase(temp_cube.begin(), temp_cube.begin() + 1);
    }

    return all_case;
}

// ����ĸ�����
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

// ������ת��˳��������麯��
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

// �޸���������(0,1,2,3 �ֱ��ʾ�޸� <1,2>,<2,4>,<4,3>,<3,1>)
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

// �޸���������(0,1,2,3 �ֱ��ʾ�޸� <1,2>,<2,4>,<4,3>,<3,1>)
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

// �޸���������(0,1,2,3 �ֱ��ʾ�޸� <1,2>,<2,4>,<4,3>,<3,1>)
nanoka_status_t Layer_Array::alter(nanoka_num_t pos, std::vector<nanoka_storage_t> data)
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

// // �޸���������(0,1,2,3 �ֱ��ʾ�޸� <1,2>,<2,4>,<4,3>,<3,1>), �������������ȥ���� (������Ȼ��������)
// nanoka_status_t Layer_Array::alter(nanoka_num_t pos, std::pair<nanoka_num_t, nanoka_num_t> data)
// {
//     try
//     {
//         storage.at(pos % data_len) = data.first;
//         storage.at((pos + 1) % data_len) = data.second;
//         return NANOKA_SUCCESS;
//     }
//     catch (std::runtime_error e)
//     {
//         std::cerr << "(Layer_Array::alter) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
//     }
//     catch (...)
//     {
//         std::cerr << "(Layer_Array::alter) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__ << "." << std::endl;
//     }
//     return NANOKA_ERROR;
// }
