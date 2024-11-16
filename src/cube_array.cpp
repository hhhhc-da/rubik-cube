#include <cube_array.hpp>

// 魔方初始化函数
nanoka_status_t Cube_Array::cube_init(void)
{
    try
    {
        // 将每个平面的所有内容都覆盖
        for (int i = 0; i < NANOKA_LAYER_NUM; ++i)
            cube_full(i, i);
        return NANOKA_SUCCESS;
    }
    catch (std::runtime_error e)
    {
        std::cerr << "(Array::cube_init) Runtime_error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "(Array::cube_init) Unknown_error: Process crushed." << std::endl;
    }
    return NANOKA_ERROR;
}

// 魔方填充函数 (使用 int 类型数据表示颜色)
nanoka_status_t Cube_Array::cube_full(nanoka_num_t layer, nanoka_num_t color)
{
    for (int i = 0; i <)
        cube_storage
}

// 魔方旋转函数
nanoka_status_t Cube_Array::cube_move(nanoka_move_t move_type, nanoka_move_enum_t move_step)
{
    switch (move_type)
    {
    case NANOKA_MOVE_YAW:
        break;
    case NANOKA_MOVE_ROLL:
        break;
    case NANOKA_MOVE_PITCH:
        break;
    default:
        throw std::runtime_error("nanoka_move_t move_type invalid.");
    }
}

// 默认构造函数
Cube_Array::Cube_Array() : cube_num(2), layer_num(6)
{
    cube_storage = new uint8_t[NANOKA_CASE_NUM * NANOKA_CASE_NUM * NANOKA_LAYER_NUM];
}

// 单一传值构造函数
Cube_Array::Cube_Array(int cube) : cube_num(cube), layer_num(6)
{
    cube_storage = new uint8_t[cube * cube * NANOKA_LAYER_NUM];
}

// 全部传值构造函数
Cube_Array::Cube_Array(int cube, int layer) : cube_num(cube), layer_num(layer)
{
    cube_storage = new uint8_t[cube * cube * layer];
}

// 析构函数回收内存
Cube_Array::~Cube_Array()
{
    delete[] cube_storage;
}