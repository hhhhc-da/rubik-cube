#include <cube_array.hpp>

// 魔方旋转函数
nanoka_status Cube_Array::cube_move(nanoka_move_t move_type, nanoka_move_enum_t move_step){
    switch(move_type){
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
Cube_Array::Cube_Array(): cube_num(2), layer_num(6) 
{
    cube_storage = new uint8_t[24];
}

// 单一传值构造函数
Cube_Array::Cube_Array(int cube) : cube_num(cube), layer_num(6)
{
    cube_storage = new uint8_t[cube*cube*6];
}

// 全部传值构造函数
Cube_Array::Cube_Array(int cube, int layer) : cube_num(cube), layer_num(layer)
{
    cube_storage = new uint8_t[cube*cube*layer];
}

// 析构函数回收内存
Cube_Array::~Cube_Array()
{
    delete[] cube_storage;
}