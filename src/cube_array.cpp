#include <cube_array.hpp>

// 魔方初始化函数
nanoka_status_t Cube_Array::cube_init(nanoka_num_t data_len, nanoka_num_t layer_num)
{
    try
    {
        // 个数校验
        if (cube_storage.size() != layer_num)
            throw std::runtime_error("cube_storage.size() != layer_num");

        // 将每个平面的所有内容都覆盖
        for (int i = 0; i < NANOKA_LAYER_NUM; ++i)
        {
            nanoka_status_t ret = cube_full(i, i);

            if (ret != NANOKA_SUCCESS)
                throw std::runtime_error("cube_full failed.");
        }
        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Cube_Array::cube_init) Runtime_error: " << e.what()  << " File " << __FILE__ << ", line " << __LINE__  << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Cube_Array::cube_init) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__  << "." << std::endl;
    }
    return NANOKA_ERROR;
}

// 魔方填充函数 (使用 int 类型数据表示颜色)
nanoka_status_t Cube_Array::cube_full(nanoka_num_t layer, nanoka_num_t color)
{
    try
    {
        nanoka_status_t ret = cube_storage.at(layer)->full(color);

        if (ret != NANOKA_SUCCESS)
            throw std::runtime_error("cube_storage.at(layer)->full(color) failed.");
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Cube_Array::cube_full) Runtime_error: " << e.what() << " File " << __FILE__ << ", line " << __LINE__  << "." << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Cube_Array::cube_full) Unknown_error: Process crushed." << " File " << __FILE__ << ", line " << __LINE__  << "." << std::endl;
    }
    return NANOKA_ERROR;
}

// 魔方旋转函数
nanoka_status_t Cube_Array::cube_move(nanoka_move_t move_type, nanoka_move_enum_t move_step)
{
    // switch (move_type)
    // {
    // case NANOKA_MOVE_YAW:
    //     break;
    // case NANOKA_MOVE_ROLL:
    //     break;
    // case NANOKA_MOVE_PITCH:
    //     break;
    // default:
    //     throw std::runtime_error("nanoka_move_t move_type invalid.");
    // }
}

// 默认构造函数
Cube_Array::Cube_Array() : cube_num(NANOKA_CASE_NUM), layer_num(NANOKA_LAYER_NUM)
{
    // 拷贝指针头
    for (nanoka_num_t i = 0; i < NANOKA_LAYER_NUM; ++i)
        cube_storage.push_back(std::make_shared<Layer_Array>(NANOKA_CASE_NUM * NANOKA_CASE_NUM));
}

// 单一传值构造函数
Cube_Array::Cube_Array(nanoka_num_t cube) : cube_num(cube), layer_num(6)
{
    for (nanoka_num_t i = 0; i < NANOKA_LAYER_NUM; ++i)
        cube_storage.push_back(std::make_shared<Layer_Array>(cube * cube));
}

// 全部传值构造函数
Cube_Array::Cube_Array(nanoka_num_t cube, nanoka_num_t layer) : cube_num(cube), layer_num(layer)
{
    for (nanoka_num_t i = 0; i < layer; ++i)
        cube_storage.push_back(std::make_shared<Layer_Array>(cube * cube));
}